#pragma once
#include <variant>
#include <abyss/scenes/Scene/Stage/Context.hpp>
#include <abyss/scenes/Scene/StageResult/Context.hpp>
#include <Siv3D/None.hpp>

namespace abyss
{
    using SceneContextHolder = std::variant<
        s3d::None_t,
        Scene::Stage::Context,
        Scene::StageResult::Context
    >;
}
