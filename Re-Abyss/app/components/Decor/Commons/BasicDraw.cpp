#include "BasicDraw.hpp"
#include <abyss/components/Decor/Commons/DecorInfo.hpp>
#include <abyss/modules/Decor/base/DecorObj.hpp>
#include <abyss/modules/Camera/Camera.hpp>
#include <abyss/modules/Decor/Decors.hpp>
#include <abyss/modules/GlobalTime/GlobalTime.hpp>

#include <Siv3D.hpp>

namespace abyss::Decor
{
    BasicDraw::BasicDraw(DecorObj* pObj):
        m_pObj(pObj)
    {}
    void BasicDraw::onStart()
    {
        m_info = m_pObj->find<DecorInfo>();
    }
    void BasicDraw::onDraw() const
    {
        auto quad = m_info->toParallaxQuad();
        auto camera = m_pObj->getModule<Camera>();
        if (!quad.intersects(camera->screenRegion())) {
            return;
        }
        auto decor = m_pObj->getModule<Decors>();
        auto time = m_pObj->getModule<GlobalTime>()->time();
        auto tex = decor
            ->getTexture(m_info->getGId(), time)
            .mirrored(m_info->isMirrored())
            .flipped(m_info->isFlipped());
        quad(tex).draw();
    }
}
