#include <abyss/scenes/SequenceManager.hpp>

#include <abyss/scenes/Scene/Boot/Scene.hpp>
#include <abyss/scenes/Scene/DevPortal/Scene.hpp>
#include <abyss/scenes/Scene/Experiment/Scene.hpp>
#include <abyss/scenes/Scene/Splash/Scene.hpp>
#include <abyss/scenes/Scene/Title/Scene.hpp>
#include <abyss/scenes/Scene/SaveSelect/Scene.hpp>
#include <abyss/scenes/Scene/Home/Scene.hpp>
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
        m_scene.add<Scene::Boot::Scene>(SceneKind::Boot);
        m_scene.add<Scene::Splash::Scene>(SceneKind::Splash);
        m_scene.add<Scene::Title::Scene>(SceneKind::Title);
        m_scene.add<Scene::SaveSelect::Scene>(SceneKind::SaveSelect);
        m_scene.add<Scene::Home::Scene>(SceneKind::Home);
        m_scene.add<Scene::Stage::Scene>(SceneKind::Stage);
        m_scene.add<Scene::StageResult::Scene>(SceneKind::StageResult);
#if ABYSS_DEVELOP
        m_scene.add<Scene::DevPortal::Scene>(SceneKind::DevPortal);
        m_scene.add<Scene::Experiment::Scene>(SceneKind::Experiment);
#endif

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
        bool pushedChild = false;
        do {
            if (m_sequence.empty()) {
                m_sequence.push(std::make_shared<RootSequence>(this));
            }
            auto top = m_sequence.top();
            success = top->onNext();
            if (top != m_sequence.top()) {
                pushedChild = true;
                continue;
            } else {
                pushedChild = false;
            }
            if (!success) {
                m_sequence.pop();
            }
        } while (!success || pushedChild);
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

