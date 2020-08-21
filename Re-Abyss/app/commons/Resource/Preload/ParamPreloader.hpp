#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/commons/ResourceManager/ResourceManager.hpp>

namespace abyss::Resource::Prelaod
{
    void LoadSplashToml(const ResourceManager& resource);

    void LoadActorToml(const ResourceManager& resource);
}