#pragma once
#include <variant>
#include <abyss/scenes/Scene/Title/SceneResult.hpp>
#include <abyss/scenes/Scene/SaveSelect/SceneResult.hpp>
#include <abyss/scenes/Scene/Stage/SceneResult.hpp>
#include <Siv3D/None.hpp>

namespace abyss
{
    using SceneResultHolder = std::variant<
        s3d::None_t,
        Scene::Title::SceneResult,
        Scene::SaveSelect::SceneResult,
        Scene::Stage::SceneResult
    >;
}
