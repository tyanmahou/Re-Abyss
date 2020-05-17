#pragma once
#include <memory>
#include <Siv3D/Fwd.hpp>
#include <abyss/commons/Fwd.hpp>

namespace abyss
{
    class SystemFactory
    {
    public:
        static std::shared_ptr<System> CreateFromTmx(const s3d::String& mapName);
        static std::shared_ptr<System> CreateFromTmx(const DIContainer* container, const s3d::String& mapName);
    };
}