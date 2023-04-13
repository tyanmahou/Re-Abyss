#pragma once
#include <abyss/scenes/SceneKind.hpp>
#include <abyss/scenes/Data/SceneContextHolder.hpp>
#include <abyss/scenes/Data/SceneResultHolder.hpp>
#include <abyss/scenes/Data/ShareData.hpp>
#include <abyss/scenes/Loading/Loader.hpp>
#include <abyss/scenes/Fade/Fader.hpp>
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
        SharedData share{};

        Loading::Loader loader;
        Fade::Fader feader;

        std::shared_ptr<User::DataStore> dataStore;
    };
}
