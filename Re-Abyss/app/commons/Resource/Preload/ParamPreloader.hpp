#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/commons/ResourceManager/ResourceManager.hpp>

namespace abyss::Resource::Prelaod
{
    void LoadTomlAll(const ResourceManager& resource);
    void LoadSplashToml(const ResourceManager& resource);
    void LoadTitleToml(const ResourceManager& resource);

    void LoadActorToml(const ResourceManager& resource);
}