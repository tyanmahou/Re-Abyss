#include <abyss/scenes/SequenceManager.hpp>

#include <abyss/scenes/Scene/Root/RootScene.hpp>
#include <abyss/scenes/Scene/Splash/SplashScene.hpp>
#include <abyss/scenes/Scene/Title/Scene.hpp>
#include <abyss/scenes/Scene/SaveSelect/SaveSelectScene.hpp>
#include <abyss/scenes/Scene/Stage/StageScene.hpp>
#include <abyss/scenes/Scene/StageResult/StageResultScene.hpp>

#include <abyss/scenes/Sequence/Root/RootSequence.hpp>

#include <abyss/debugs/System/System.hpp>

namespace abyss
{
    SequenceManager::SequenceManager()
    {
        m_scene.add<RootScene>(SceneKind::Root);
        m_scene.add<SplashScene>(SceneKind::Splash);
        m_scene.add<Title::Scene>(SceneKind::Title);
        m_scene.add<SaveSelectScene>(SceneKind::SaveSelect);
        m_scene.add<StageScene>(SceneKind::Stage);
        m_scene.add<StageResultScene>(SceneKind::StageResult);

#if ABYSS_DEBUG
        Debug::System::SetContext(Debug::SystemContext{
            .pScene = &m_scene
        });
#endif
        this->pushSequence<RootSequence>(this);
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
        return m_scene.update();
    }
    const SceneResultHolder& SequenceManager::getResult() const
    {
        return m_scene.get()->result;
    }
    bool SequenceManager::changeNext()
    {
        bool success = false;
        do {
            if (m_sequence.empty()) {
                return false;
            }
            auto top = m_sequence.top();
            success = top->onNext();
            if (!success) {
                m_sequence.pop();
            }
        } while (!success);
        return success;
    }
    void SequenceManager::changeScene(const SceneKind& state, int transitionTimeMillisec, const s3d::CrossFade crossFade)
    {
        auto data = m_scene.get();
        data->fromScene = data->toScene;
        data->toScene = state;
        m_scene.changeScene(state, transitionTimeMillisec, crossFade);
    }
    void SequenceManager::pushSequence(std::shared_ptr<ISequence> child)
    {
        m_sequence.push(child);
        child->onNext();
    }
}

