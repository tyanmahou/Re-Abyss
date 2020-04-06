#pragma once
#include <memory>
#include <Siv3D/Fwd.hpp>
#include <abyss/commons/Fwd.hpp>
#include <abyss/controllers/Stage/Stage.hpp>

namespace abyss
{
    class StageFactory
    {
    public:
        static std::unique_ptr<Stage> CreateFromTmx(const s3d::FilePath& tmx);
    };
}