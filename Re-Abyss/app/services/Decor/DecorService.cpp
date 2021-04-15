#include "DecorService.hpp"

#include <abyss/datastores/Decor/base/IDecorDataStore.hpp>
#include <abyss/datastores/Decor/base/IAnimationDataStore.hpp>
#include <abyss/datastores/Decor/base/IGraphicsDataStore.hpp>
#include <abyss/datastores/Actors/Gimmick/base/IGimmickDataStore.hpp>
#include <abyss/datastores/Actors/Map/base/ITileMapDataStore.hpp>

#include <Siv3D.hpp>
namespace abyss::decor
{
    DecorService::DecorService(
        std::shared_ptr<IDecorDataStore>decor, 
        std::shared_ptr<IGimmickDataStore>gimmick,
        std::shared_ptr<ITileMapDataStore>map,
        std::shared_ptr<IGraphicsDataStore> graphics,
        std::shared_ptr<IAnimationDataStore> animation
    )
    {
        m_front = decor->select(DecorGroup::Front);
        m_back = decor->select(DecorGroup::Back);

        m_graphics = graphics->selectWithKey();
        m_animation = animation->selectWithKey();

        {
            auto grid = map->selectRawGrid();
            for (uint32 y = 0; y < grid.height(); ++y) {
                for (uint32 x = 0; x < grid.width(); ++x) {
                    auto gId = grid[y][x];
                    if (gId == 0) {
                        continue;
                    }
                    const auto& graphic = m_graphics[gId];

                    auto& model = m_tileMap[graphic.filePath];

                    if (model.isEmpty()) {
                        // 初期化
                        model.setFilePath(graphic.filePath);
                        model.resize(grid.width(), grid.height());
                    }
                    model[y][x] = gId;
                }
            }
        }
    }
    void DecorServiceInstaller::onBinding(emaject::Container* container) const
    {
        container->bind<IDecorService>()
            .to<DecorService>()
            .asCache();
    }
    s3d::Array<std::shared_ptr<DecorEntity>> DecorService::getTileMap(const s3d::RectF& screen) const
    {
        s3d::Array<std::shared_ptr<DecorEntity>> ret;
        return ret;
    }
}
