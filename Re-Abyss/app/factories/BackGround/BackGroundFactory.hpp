#pragma once
#include <memory>
#include <Siv3D/String.hpp>
#include <abyss/commons/Fwd.hpp>

namespace abyss
{
    class BackGroundFactory
    {
    public:
        static std::shared_ptr<BackGround> CreateFromTmx(const s3d::String& mapName);
        static std::shared_ptr<BackGround> CreateFromTmx(const DIContainer* container, const s3d::String& mapName);

    };
}