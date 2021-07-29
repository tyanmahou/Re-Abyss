#include "DecorService.hpp"

#include <abyss/datastores/Decor/base/IDecorDataStore.hpp>
#include <abyss/datastores/Decor/base/IAnimationDataStore.hpp>
#include <abyss/datastores/Decor/base/IGraphicsDataStore.hpp>
#include <abyss/datastores/Actor/Gimmick/base/IGimmickDataStore.hpp>
#include <abyss/datastores/Actor/Map/base/ITileMapDataStore.hpp>

#include <Siv3D.hpp>
namespace abyss::Decor
{
    DecorService::DecorService(
        std::shared_ptr<IDecorDataStore>decor, 
        std::shared_ptr<Actor::Map::ITileMapDataStore>map,
        std::shared_ptr<IGraphicsDataStore> graphics,
        std::shared_ptr<IAnimationDataStore> animation
    )
    {
        m_decors = decor->select();
        m_graphics = graphics->selectWithKey();
        m_animation = animation->selectWithKey();

        {
            for (auto&& grid : map->selectRawGrid()) {
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
                            model
                                .setFilePath(graphic.filePath)
                                .setTileSize(map->getTileSize())
                                .setFirstGId(graphic.firstGId)
                                ;
                            model.resize(grid.width(), grid.height());
                        }
                        model[y][x] = gId;
                    }
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
    s3d::Array<Map::TileMapModel> DecorService::getTileMap(const s3d::RectF& screen) const
    {
        s3d::Array<Map::TileMapModel> ret;
        for (auto&& [path, tileMap] : m_tileMap) {
            const Vec2& tileSize = tileMap.getTileSize();
            const Size& mapSize = tileMap.size();
            uint32 xStart = Max<uint32>(0, static_cast<uint32>(screen.x / tileSize.x));
            uint32 yStart = Max<uint32>(0, static_cast<uint32>(screen.y / tileSize.y));

            uint32 xEnd = Min<uint32>(mapSize.x, xStart + static_cast<uint32>(screen.w / tileSize.x));
            uint32 yEnd = Min<uint32>(mapSize.y, yStart + static_cast<uint32>(screen.h / tileSize.y));

            Map::TileMapModel model;
            model
                .setPos(Vec2{ xStart * tileSize.x, yStart * tileSize.y })
                .setFilePath(path)
                .setTileSize(tileSize)
                .setFirstGId(tileMap.getFirstGId())
                .resize(xEnd - xStart + 1, yEnd - yStart + 1);
            for (uint32 y = yStart; y <= yEnd; ++y) {
                for (uint32 x = xStart; x <= xEnd; ++x) {
                    uint32 gId = tileMap[y][x];
                    model[y - yStart][x - xStart] = gId;
                }
            }
            ret.push_back(std::move(model));
        }
        return ret;
    }
}
