#include <abyss/scenes/SequenceManager.hpp>

#include <abyss/scenes/Scene/EntryPoint/Scene.hpp>
#include <abyss/scenes/Scene/Experiment/Scene.hpp>
#include <abyss/scenes/Scene/Splash/Scene.hpp>
#include <abyss/scenes/Scene/Title/Scene.hpp>
#include <abyss/scenes/Scene/SaveSelect/Scene.hpp>
#include <abyss/scenes/Scene/Stage/Scene.hpp>
#include <abyss/scenes/Scene/StageResult/Scene.hpp>

#include <abyss/scenes/Sequence/Root/RootSequence.hpp>
#include <abyss/utils/Enum/EnumTraits.hpp>
#include <abyss/debugs/Debug.hpp>
#include <abyss/debugs/System/System.hpp>

namespace abyss
{
    SequenceManager::SequenceManager()
    {
        m_scene.add<Scene::EntryPoint::Scene>(SceneKind::EntryPoint);
        m_scene.add<Scene::Splash::Scene>(SceneKind::Splash);
        m_scene.add<Scene::Title::Scene>(SceneKind::Title);
        m_scene.add<Scene::SaveSelect::Scene>(SceneKind::SaveSelect);
        m_scene.add<Scene::Stage::Scene>(SceneKind::Stage);
        m_scene.add<Scene::StageResult::Scene>(SceneKind::StageResult);
        m_scene.add<Scene::Experiment::Scene>(SceneKind::Experiment);

#if ABYSS_DEBUG
        Debug::System::SetContext(Debug::SystemContext{
            .pSequence = this
        });
#endif
        data()->isRequestedSceneEnd = true;
    }
    bool SequenceManager::update()
    {
        auto data = m_scene.get();
        if (data->isRequestedSceneEnd) {
            data->isRequestedSceneEnd = false;
            if (!this->changeNext()) {
                return false;
            }
        }
        if (m_isExit) {
            return false;
        }
        return m_scene.update();
    }
    const SceneResultHolder& SequenceManager::getResult() const
    {
        return m_scene.get()->result;
    }
    SequecneData* SequenceManager::data()
    {
        return m_scene.get().get();
    }
    const SequecneData* SequenceManager::data() const
    {
        return m_scene.get().get();
    }
    bool SequenceManager::changeNext()
    {
        bool success = false;
        do {
            if (m_sequence.empty()) {
                m_sequence.push(std::make_shared<RootSequence>(this));
            }
            auto top = m_sequence.top();
            success = top->onNext();
            if (top != m_sequence.top()) {
                continue;
            }
            if (!success) {
                m_sequence.pop();
            }
        } while (!success);
        return success;
    }
    void SequenceManager::exit()
    {
        m_isExit = true;
    }
    void SequenceManager::changeScene(const SceneKind& state, s3d::int32 transitionTimeMillisec, const s3d::CrossFade crossFade)
    {
        auto data = m_scene.get();
        data->fromScene = data->toScene;
        data->toScene = state;
        m_scene.changeScene(state, transitionTimeMillisec, crossFade);
#if ABYSS_DEBUG
        Debug::Log::Info(U"[Scene Load] {}"_fmt(Enum::ToStr(state)));
#endif
    }
    void SequenceManager::changeSequence(std::shared_ptr<ISequence> child)
    {
        std::stack<std::shared_ptr<ISequence>> empty;
        m_sequence.swap(empty);
        m_sequence.push(child);
        data()->isRequestedSceneEnd = true;
    }
    void SequenceManager::pushSequence(std::shared_ptr<ISequence> child)
    {
        m_sequence.push(child);
    }
}

