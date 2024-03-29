#pragma once
#include <Emaject.hpp>
#include <Siv3D/String.hpp>
namespace abyss::Factory::Stage
{
    emaject::Injector Injector(const s3d::String& mapPath);
    void Install(emaject::Injector& injector, const s3d::String& mapPath);
}
