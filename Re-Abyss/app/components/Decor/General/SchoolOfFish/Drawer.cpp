#include "Drawer.hpp"
#include <Siv3D.hpp>
#include <abyss/modules/Decor/base/DecorObj.hpp>
#include <abyss/modules/GlobalTime/GlobalTime.hpp>

namespace abyss::Decor::General::SchoolOfFish
{
    Drawer::Drawer(DecorObj* pObj):
        m_pObj(pObj)
    {}

    void Drawer::onStart()
    {

    }
    void Drawer::onDraw() const
    {
        ScopedRenderStates2D blend(s3d::BlendState::Subtractive);
        auto scopedShader = m_shader
            .setTime(m_pObj->getModule<GlobalTime>()->time())
            .start();
        s3d::Graphics2D::DrawTriangles(64 * 8 * 2);
    }
}