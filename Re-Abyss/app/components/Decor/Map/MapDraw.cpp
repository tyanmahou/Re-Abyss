#include "MapDraw.hpp"

#include <abyss/components/Decor/Commons/DecorInfo.hpp>
#include <abyss/modules/Decor/base/DecorObj.hpp>
#include <abyss/modules/Camera/Camera.hpp>
#include <abyss/modules/Decor/Decor.hpp>
#include <abyss/modules/GlobalTime/GlobalTime.hpp>

#include <Siv3D.hpp>

namespace abyss::decor::Map
{
    MapDraw::MapDraw(DecorObj* pObj):
        m_pObj(pObj)
    {}

    void MapDraw::onStart()
    {
        m_info = m_pObj->find<DecorInfo>();
    }

    void MapDraw::onDraw() const
    {
        auto camera = m_pObj->getModule<Camera>();
        auto rect = m_info->toRect();
        if (!rect.intersects(camera->screenRegion())) {
            return;
        }

        auto decor = m_pObj->getModule<Decor>();
        auto time = m_pObj->getModule<GlobalTime>()->time();
        decor->getTexture(m_info->getGId(), time).draw(rect.pos);
    }

}
