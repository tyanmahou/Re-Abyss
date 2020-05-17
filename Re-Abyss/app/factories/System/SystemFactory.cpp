#include "SystemFactory.hpp"
#include <abyss/controllers/System/System.hpp>
#include <abyss/factories/DIContainer/DIContainer.hpp>
#include <abyss/factories/Stage/StageFactory.hpp>

namespace abyss
{
    std::shared_ptr<System> SystemFactory::CreateFromTmx(const s3d::FilePath& mapName)
    {
        DIContainer c;
        return CreateFromTmx(&c, mapName);
    }
    std::shared_ptr<System> SystemFactory::CreateFromTmx(const DIContainer* container, const s3d::String& mapName)
    {
        // stage
        auto stage = StageFactory::CreateFromTmx(container, mapName);

        container->regist<System>([&](const DIContainer*) {
            return std::make_shared<System>(stage);
        });
        return container->get<System>();
    }
}
