#include "Builder.hpp"
#include <abyss/components/Decor/Commons/CustomDraw.hpp>

#include <abyss/modules/Decor/base/DecorObj.hpp>
#include <abyss/models/Decor/Map/TileMapModel.hpp>

#include <abyss/modules/Decor/Decor.hpp>
#include <abyss/modules/GlobalTime/GlobalTime.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <Siv3D.hpp>

namespace
{
    class Drawer;
}
namespace abyss::decor::Map::TileMap
{
    void Builder::Build(DecorObj* pObj, const TileMapModel& tileMap)
    {
        pObj->attach<CustomDraw>()->setDrawer<Drawer>(pObj, tileMap);
    }
}

namespace
{
    using namespace abyss;
    using namespace abyss::decor;
    using namespace abyss::decor::Map;

    class Drawer : public CustomDraw::IImpl
    {
    public:
        Drawer(DecorObj* pObj, const TileMapModel& tileMap):
            m_pObj(pObj),
            m_tileMap(tileMap),
            m_mapChip(Resource::Assets::Main()->loadTexture(tileMap.getFilePath(), Path::Root)),
            m_gId(tileMap.size(), Palette::White)
        {}
        void onStart()
        {

        }
        void onDraw() const
        {
            auto decor = m_pObj->getModule<Decor>();
            auto time = m_pObj->getModule<GlobalTime>()->time();

            const auto& grid = m_tileMap.gIds();
            const auto& pos = m_tileMap.getPos();
            const auto& tileSize = m_tileMap.getTileSize();
            for (uint32 y = 0; y < grid.height(); ++y) {
                for (uint32 x = 0; x < grid.width(); ++x) {
                    auto gId = grid[y][x];
                    if (gId == 0) {
                        continue;
                    }
                    decor->getTexture(gId, time).draw(pos + tileSize * Vec2{x, y});
                }
            }
        }
    private:
        DecorObj* m_pObj;
        TileMapModel m_tileMap;
        Texture m_mapChip;
        DynamicTexture m_gId;
    };
}