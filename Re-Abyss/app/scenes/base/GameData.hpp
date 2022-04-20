#pragma once
#include <variant>
#include <abyss/scenes/base/ShareData.hpp>
#include <abyss/scenes/Main/MainSceneContext.hpp>
#include <abyss/scenes/ClearResult/ClearResultSceneContext.hpp>
#include <Siv3D/String.hpp>
#include <Siv3D/Optional.hpp>

namespace abyss
{
    using SceneContext = std::variant<
        s3d::None_t,
        MainSceneContext,
        ClearResultSceneContext
    >;

    /// <summary>
    /// game shared data
    /// </summary>
    struct GameData
    {
        ShareData shareData{};
        SceneContext context{ s3d::none };
        s3d::String fromScene;
        s3d::String toScene;
    };
}