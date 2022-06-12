#include <abyss/scenes/SequenceManager.hpp>

#include <abyss/scenes/Scene/Root/RootScene.hpp>
#include <abyss/scenes/Scene/Splash/SplashScene.hpp>
#include <abyss/scenes/Scene/Title/TitleScene.hpp>
#include <abyss/scenes/Scene/SaveSelect/SaveSelectScene.hpp>
#include <abyss/scenes/Scene/Stage/StageScene.hpp>
#include <abyss/scenes/Scene/StageResult/StageResultScene.hpp>

#include <abyss/debugs/System/System.hpp>

namespace abyss
{
    SequenceManager::SequenceManager()
    {
        m_scene.add<RootScene>(SceneKind::Root);
        m_scene.add<SplashScene>(SceneKind::Splash);
        m_scene.add<TitleScene>(SceneKind::Title);
        m_scene.add<SaveSelectScene>(SceneKind::SaveSelect);
        m_scene.add<StageScene>(SceneKind::Stage);
        m_scene.add<StageResultScene>(SceneKind::StageResult);

#if ABYSS_DEBUG
        Debug::System::SetContext(Debug::SystemContext{
            .pScene = &m_scene
        });
#endif
    }
    bool SequenceManager::update()
    {
        return m_scene.update();
    }
}

