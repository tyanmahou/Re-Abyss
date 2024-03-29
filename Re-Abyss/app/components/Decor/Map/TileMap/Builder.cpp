#include <abyss/components/Decor/Map/TileMap/Builder.hpp>
#include <abyss/components/Decor/Common/CustomDraw.hpp>

#include <abyss/modules/Decor/base/DecorObj.hpp>
#include <abyss/modules/GlobalTime/GlobalTime.hpp>
#include <abyss/views/Decor/Map/TileMapView.hpp>


namespace
{
    class Drawer;
}
namespace abyss::Decor::Map::TileMap
{
    void Builder::Build(DecorObj* pObj, const TileMapData& tileMap)
    {
        pObj->attach<CustomDraw>()
            ->setDrawer<Drawer>(pObj, tileMap)
            .setLayer(DrawLayer::Land);
    }
}

namespace
{
    using namespace abyss;
    using namespace abyss::Decor;
    using namespace abyss::Decor::Map;
    class Drawer : public CustomDraw::IImpl
    {
    public:
        Drawer(DecorObj* pObj, const TileMapData& tileMap) :
            m_pObj(pObj),
            m_view(tileMap)
        {}
        void onStart()
        {
        }
        void onDraw() const
        {
            auto decor = m_pObj->getModule<Decors>();
            auto time = m_pObj->getModule<GlobalTime>()->time();
            m_view.draw(*decor, time);
        }
    private:
        DecorObj* m_pObj;
        TileMapView m_view;
    };
}
