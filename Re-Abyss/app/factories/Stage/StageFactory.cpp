#include "StageFactory.hpp"
#include <abyss/controllers/Stage/Stage.hpp>
#include <abyss/datastores/Stage/TiledStageDataStore.hpp>
#include <abyss/repositories/Stage/StageRepository.hpp>
#include <abyss/views/Stage/StageView.hpp>

#include <abyss/factories/DIContainer/DIContainer.hpp>
#include <abyss/factories/BackGround/BackGroundFactory.hpp>
#include <abyss/factories/Decor/DecorFactory.hpp>

namespace abyss
{
    std::shared_ptr<Stage> StageFactory::CreateFromTmx(const s3d::String& mapName)
    {
        DIContainer c;
        return CreateFromTmx(&c, mapName);

    }
    std::shared_ptr<Stage> StageFactory::CreateFromTmx(const DIContainer* container, const s3d::String& mapName)
    {
        auto decor = DecorFactory::CreateFromTmx(container, mapName);
        auto bg = BackGroundFactory::CreateFromTmx(container, mapName);

        container->regist<IStageDataStore>([&mapName](const DIContainer*) {
            return std::make_shared<TiledStageDataStore>(mapName);
        });
        container->regist<IStageRepository>([&mapName](const DIContainer* c) {
            return std::make_shared<StageRepository>(c->get<IStageDataStore>());
        });

        container->regist<IStageRepository>([&mapName](const DIContainer* c) {
            return std::make_shared<StageRepository>(c->get<IStageDataStore>());
        });

        container->regist<IStageView>([&](const DIContainer*) {
            auto view = std::make_shared<StageView>();
            view->setBg(bg.get());
            view->setDecor(decor.get());
            return view;
        });
        container->regist<Stage>([&](const DIContainer* c) {
            return std::make_shared<Stage>(
                c->get<IStageRepository>(),
                c->get<IStageView>(),
                decor,
                bg
            );
        });
        return container->get<Stage>();
    }
}
