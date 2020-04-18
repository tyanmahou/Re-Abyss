#include "ActionSystemFactory.hpp"
#include <abyss/controllers/ActionSystem/ActionSystem.hpp>
#include <abyss/factories/DIContainer/DIContainer.hpp>
#include <abyss/factories/Stage/StageFactory.hpp>

namespace abyss
{
    std::shared_ptr<ActionSystem> ActionSystemFactory::CreateFromTmx(const s3d::FilePath& mapName)
    {
        DIContainer c;
        return CreateFromTmx(&c, mapName);
    }
    std::shared_ptr<ActionSystem> ActionSystemFactory::CreateFromTmx(const DIContainer* container, const s3d::String& mapName)
    {
        // stage
        auto stage = StageFactory::CreateFromTmx(container, mapName);

        container->regist<ActionSystem>([&](const DIContainer*) {
            return std::make_shared<ActionSystem>(stage);
        });
        return container->get<ActionSystem>();
    }
}
