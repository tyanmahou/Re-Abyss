#pragma once
#include <abyss/scenes/SceneKind.hpp>
#include <abyss/scenes/Data/SceneContextHolder.hpp>
#include <abyss/scenes/Data/SceneResultHolder.hpp>
#include <abyss/scenes/Loading/Loader.hpp>
#include <abyss/modules/Fade/SceneFader.hpp>
#include <abyss/modules/Sound/SceneSound.hpp>
#include <abyss/modules/User/DataStore.hpp>
#include <Siv3D/String.hpp>
#include <Siv3D/Optional.hpp>

namespace abyss
{

    /// <summary>
    /// SequecneData
    /// </summary>
    struct SequecneData
    {
        SceneContextHolder context{ s3d::none };
        SceneResultHolder result{s3d::none};
        bool isRequestedSceneEnd{};
        SceneKind fromScene{};
        SceneKind toScene{};

        std::shared_ptr<Sound::SceneSound> sound;
        Loading::Loader loader;
        Fade::SceneFader fader;

        std::shared_ptr<User::DataStore> dataStore;
    };
}
