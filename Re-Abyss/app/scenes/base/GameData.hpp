#pragma once
#include <variant>
#include <abyss/scenes/SceneKind.hpp>
#include <abyss/scenes/base/ShareData.hpp>
#include <abyss/scenes/Scene/Stage/StageSceneContext.hpp>
#include <abyss/scenes/Scene/StageResult/StageResultSceneContext.hpp>
#include <Siv3D/String.hpp>
#include <Siv3D/Optional.hpp>

namespace abyss
{
    using SceneContext = std::variant<
        s3d::None_t,
        StageSceneContext,
        StageResultSceneContext
    >;

    /// <summary>
    /// game shared data
    /// </summary>
    struct GameData
    {
        ShareData shareData{};
        SceneContext context{ s3d::none };
        SceneKind fromScene;
        SceneKind toScene;
    };
}
