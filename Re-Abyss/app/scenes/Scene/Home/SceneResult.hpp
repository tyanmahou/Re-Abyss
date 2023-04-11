#pragma once
#include <Siv3D/String.hpp>
#include <abyss/values/StageDef.hpp>

namespace abyss::Scene::Home
{
    struct SceneResult
    {
        StageDef stage;
        bool isBack = false;
    };
}
