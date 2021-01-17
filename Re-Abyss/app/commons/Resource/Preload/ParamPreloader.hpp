#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>

namespace abyss::Resource::Prelaod
{
    void LoadTomlAll(const Assets& resource);
    void LoadSplashToml(const Assets& resource);
    void LoadTitleToml(const Assets& resource);
    void LoadSaveSelectToml(const Assets& resource);

    void LoadActorToml(const Assets& resource);
    void LoadUIToml(const Assets& resource);
}