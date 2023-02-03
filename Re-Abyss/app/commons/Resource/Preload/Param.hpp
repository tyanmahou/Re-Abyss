#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>

namespace abyss::Resource::Preload
{
    void LoadTomlAll(const Assets* resource = Assets::Main());
    void LoadCycleCommon(const Assets* resource = Assets::Main());

    void LoadSplashToml(const Assets* resource = Assets::Main());
    void LoadTitleToml(const Assets* resource = Assets::Main());
    void LoadSaveSelectToml(const Assets* resource = Assets::Main());

    void LoadActorToml(const Assets* resource = Assets::Main());
    void LoadUIToml(const Assets* resource = Assets::Main());
    void LoadLoadingToml(const Assets* resource = Assets::Main());
}
