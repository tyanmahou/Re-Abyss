#include "TileMapView.hpp"

#include <abyss/modules/Decor/Decors.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <Siv3D.hpp>

namespace abyss::Decor::Map
{
    TileMapView::TileMapView(const TileMapModel& tileMap):
        m_tileMap(tileMap),
        m_texture(Image(tileMap.size()* tileMap.getTileSize().asPoint()))
    {
        m_shader
            .setTextureSize(m_texture.size())
            .setMapChip(Resource::Assets::Main()->loadTexture(tileMap.getFilePath(), Path::Root), tileMap.getTileSize());

        const auto& grid = m_tileMap.gIds();
        bool isFind = false;
        for (int32 y = grid.indexBegin(); y < grid.indexEnd(); ++y) {
            const auto& row = grid[y];
            for (int32 x = row.indexBegin(); x < grid.indexEnd(); ++x) {
                auto gId = row[x];
                if (gId == 0) {
                    isFind = false;
                    continue;
                }
                if (!isFind) {
                    m_indexPoints.emplace_back(x, y);
                    isFind = true;
                }
            }
        }
    }

    void TileMapView::draw(const Decors& decor, double time) const
    {
        if (m_indexPoints.empty()) {
            // 描画するものがない
            return;
        }
        Image image(m_tileMap.size());
        image.fill(ColorF(0, 0));
        const auto& grid = m_tileMap.gIds();
        auto firstGId = m_tileMap.getFirstGId();
        const auto& startIndex = m_tileMap.startIndex();
        auto imageAnim = [&](const Size& indexPoint) {
            int32 y = indexPoint.y;
            int32 x = indexPoint.x;
            for (; y < grid.indexEnd(); ++y) {
                const auto& row = grid[y];
                for (; x < row.indexEnd(); ++x) {
                    auto gId = row[x];
                    if (gId == 0) {
                        return;
                    }
                    if (firstGId <= gId) {
                        image[y - startIndex.y][x - startIndex.x] = Color(decor.getAnimGId(gId, time) - firstGId, 0, 0);
                    }
                }
                x = 0;
            }
        };
        for (auto& indexPoint : m_indexPoints) {
            imageAnim(indexPoint);
        }

        {
            auto scoped = m_shader.start(std::move(image));
            m_texture.draw(m_tileMap.getPos());
        }
    }

}
