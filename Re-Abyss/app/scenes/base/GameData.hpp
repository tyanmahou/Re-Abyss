#pragma once
#include <variant>
#include <abyss/scenes/SceneKind.hpp>
#include <abyss/scenes/Scene/Title/SceneResult.hpp>
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
    using SceneResultHolder = std::variant<
        s3d::None_t,
        Title::SceneResult
    >;
    /// <summary>
    /// game shared data
    /// </summary>
    struct GameData
    {
        SceneContext context{ s3d::none };
        SceneResultHolder result{s3d::none};
        bool isRequestedSceneEnd{};
        SceneKind fromScene{};
        SceneKind toScene{};
    };
}
