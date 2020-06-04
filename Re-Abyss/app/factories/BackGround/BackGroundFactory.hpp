#pragma once
#include <memory>
#include <Siv3D/String.hpp>
#include <abyss/commons/Fwd.hpp>

namespace abyss
{
    class BackGroundFactory
    {
    public:
        static void BuildFromTmx(const DIContainer* container, const s3d::String& mapName);
    };
}