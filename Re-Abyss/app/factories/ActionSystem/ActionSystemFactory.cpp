#include "ActionSystemFactory.hpp"

#include <abyss/controllers/ActionSystem/ActionSystem.hpp>

#include <abyss/controllers/Stage/Stage.hpp>
#include <abyss/datastores/Stage/TiledStageDataStore.hpp>
#include <abyss/repositories/Stage/StageRepository.hpp>
#include <abyss/views/Stage/TiledStageView.hpp>

namespace abyss
{
    std::unique_ptr<ActionSystem> ActionSystemFactory::CreateFromTmx(const s3d::FilePath& tmx)
    {
        // stage
        auto stageDataStore = std::make_unique<TiledStageDataStore>(tmx);
        auto stageRepository = std::make_unique<StageRepository>(*stageDataStore);
        auto stageView = std::make_unique<TiledStageView>(stageDataStore->getTiledMap());
        auto stage = std::make_unique<Stage>(std::move(stageRepository), std::move(stageView));

        return std::make_unique<ActionSystem>(std::move(stage));
    }
}
