#pragma once
#include <memory>
#include <Siv3D/String.hpp>
#include <abyss/commons/Fwd.hpp>

namespace abyss
{
    class DecorFactory
    {
    public:
        static std::shared_ptr<Decor> CreateFromTmx(const s3d::String& mapName);
        static std::shared_ptr<Decor> CreateFromTmx(const DIContainer* container, const s3d::String& mapName);

    };
}