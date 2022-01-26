#include <abyss/services/Decor/DecorService.hpp>

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
            for (const auto& chunk : map->selectGrid()) {
                for (int32 y = chunk.indexBegin(); y < chunk.indexEnd(); ++y) {
                    const auto& row = chunk[y];
                    for (int32 x = row.indexBegin(); x < row.indexEnd(); ++x) {
                        auto&& entity = row[x];
                        auto gId = entity.gId;
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
                        }
                        model[y][x] = Map::TileModel{
                            .gId = entity.gId,
                            .col = static_cast<uint32>(entity.col)
                        };
                    }
                }
            }
            for (auto&& [key, elm] : m_tileMap) {
                m_tileMap[key].calcSize();
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

            auto [xStart, yStart] = tileMap.startIndex();
            xStart = static_cast<int32>(Max(xStart, static_cast<int32>(screen.x / tileSize.x)));
            yStart = static_cast<int32>(Max(yStart, static_cast<int32>(screen.y / tileSize.y)));

            auto [xEnd, yEnd] = tileMap.endIndex();
            xEnd = Min<int32>(xEnd, xStart + static_cast<int32>(screen.w / tileSize.x));
            yEnd = Min<int32>(yEnd, yStart + static_cast<int32>(screen.h / tileSize.y));

            Map::TileMapModel model;
            model
                .setPos(Vec2{ xStart * tileSize.x, yStart * tileSize.y })
                .setFilePath(path)
                .setTileSize(tileSize)
                .setFirstGId(tileMap.getFirstGId());

            for (int32 y = yStart; y <= yEnd; ++y) {
                for (int32 x = xStart; x <= xEnd; ++x) {
                    auto&& tile = tileMap[y][x];
                    model[y][x] = tile;
                }
            }
            model.calcSize();
            ret.push_back(std::move(model));
        }
        return ret;
    }
}
