#include "Builder.hpp"
#include <abyss/components/Decor/Commons/CustomDraw.hpp>

#include <abyss/modules/Decor/base/DecorObj.hpp>
#include <abyss/modules/GlobalTime/GlobalTime.hpp>
#include <abyss/views/Decor/Map/TileMapView.hpp>


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
        Drawer(DecorObj* pObj, const TileMapModel& tileMap) :
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