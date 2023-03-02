#pragma once
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <Emaject.hpp>

namespace abyss::Factory::Adv
{
    emaject::Injector Injector();
    emaject::Injector Injector(const s3d::FilePath& path, Resource::Assets* pAssets);
}
