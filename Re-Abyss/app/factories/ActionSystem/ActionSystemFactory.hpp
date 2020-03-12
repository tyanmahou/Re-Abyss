#pragma once
#include <memory>
#include <Siv3D/Fwd.hpp>
#include <abyss/commons/Fwd.hpp>

namespace abyss
{
    class ActionSystemFactory
    {
    public:
        static std::unique_ptr<ActionSystem> CreateFromTmx(const s3d::FilePath& tmx);
    };
}