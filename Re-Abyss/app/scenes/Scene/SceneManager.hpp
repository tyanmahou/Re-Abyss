#pragma once
#include <abyss/scenes/Data/SequecneData.hpp>
#include <abyss/scenes/SceneKind.hpp>
#include <Siv3D/SceneManager.hpp>

namespace abyss
{
    using SceneManager = s3d::SceneManager<SceneKind, SequecneData>;
}
