#include "ActionSystemFactory.hpp"

#include <abyss/controllers/ActionSystem/ActionSystem.hpp>
#include <abyss/factories/Stage/StageFactory.hpp>

namespace abyss
{
    std::unique_ptr<ActionSystem> ActionSystemFactory::CreateFromTmx(const s3d::FilePath& tmx)
    {
        // stage
        auto stage = StageFactory::CreateFromTmx(tmx);
        return std::make_unique<ActionSystem>(std::move(stage));
    }
}
