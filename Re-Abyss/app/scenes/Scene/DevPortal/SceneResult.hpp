#pragma once
#if ABYSS_DEVELOP
namespace abyss::Scene::DevPortal
{
    struct SceneResult
    {
        enum Command
        {
            GameStart,
            Experience,
        };
        Command command;
    };
}
#endif
