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
        constexpr s3d::int32 column = 64;
        constexpr s3d::int32 row = 8;
        ScopedRenderStates2D blend(s3d::BlendState::Subtractive);
        auto scopedShader = m_shader
            .setPos(s3d::Scene::CenterF())
            .setSpeed(175.0)
            .setAngle(10_deg)
            .setHightOffset(180.0)
            .setTime(m_pObj->getModule<GlobalTime>()->time())
            .setSize(column, row)
            .start();
        s3d::Graphics2D::DrawTriangles(column * row * 2);
    }
}