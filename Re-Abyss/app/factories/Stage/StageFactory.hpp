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
        static std::shared_ptr<Stage> CreateFromTmx(const s3d::String& mapName);
        static std::shared_ptr<Stage> CreateFromTmx(const DIContainer* container, const s3d::String& mapName);
    };
}