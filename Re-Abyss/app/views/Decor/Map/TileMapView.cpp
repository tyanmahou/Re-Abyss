#include "TileMapView.hpp"

#include <abyss/modules/Decor/Decor.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <Siv3D.hpp>
namespace abyss::decor::Map
{
    TileMapView::TileMapView(const TileMapModel& tileMap):
        m_tileMap(tileMap),
        m_texture(Image(tileMap.size()* tileMap.getTileSize().asPoint()))
    {
        m_shader
            .setTextureSize(m_texture.size())
            .setMapChip(Resource::Assets::Main()->loadTexture(tileMap.getFilePath(), Path::Root), tileMap.getTileSize());
    }

    void TileMapView::draw(const Decor& decor, double time) const
    {
        Image image(m_tileMap.size());
        image.fill(ColorF(0, 0));
        const auto& grid = m_tileMap.gIds();
        auto firstGId = m_tileMap.getFirstGId();
        for (uint32 y = 0; y < grid.height(); ++y) {
            for (uint32 x = 0; x < grid.width(); ++x) {
                auto gId = grid[y][x];
                if (gId == 0) {
                    continue;
                }
                if (firstGId <= gId) {
                    image[y][x] = Color(decor.getAnimGId(gId, time) - firstGId, 0, 0);
                }
            }
        }

        {
            auto scoped = m_shader.start(std::move(image));
            m_texture.draw(m_tileMap.getPos());
        }
    }

}
