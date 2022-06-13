#pragma once
#include <Siv3D/Types.hpp>

namespace abyss::Scene::SaveSelect
{
    struct SceneResult
    {
        s3d::int32 userId = 0;
        bool isNewGame = false;
        bool isBack = false;
    };
}
