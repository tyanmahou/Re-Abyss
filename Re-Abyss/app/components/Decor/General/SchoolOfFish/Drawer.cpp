#include "Drawer.hpp"
#include <Siv3D.hpp>
#include <abyss/modules/Decor/base/DecorObj.hpp>
#include <abyss/modules/Camera/Camera.hpp>
#include <abyss/modules/GlobalTime/GlobalTime.hpp>

namespace abyss::Decor::General::SchoolOfFish
{
    Drawer::Drawer(DecorObj* pObj, const SchoolOfFishEntity& entity):
        m_pObj(pObj),
        m_entity(entity)
    {}

    void Drawer::onStart()
    {

    }
    void Drawer::onDraw() const
    {
        const auto& cameraPos = m_pObj->getModule<Camera>()->getPos();
        Vec2 pos = m_entity.pos + cameraPos - cameraPos * m_entity.parallax;

        ScopedRenderStates2D blend(s3d::BlendState::Subtractive);
        auto scopedShader = m_shader
            .setPos(pos)
            .setSpeed(m_entity.speed)
            .setAngle(s3d::ToRadians(m_entity.rotation))
            .setHeightOffset(m_entity.heightOffset)
            .setAmplitude(m_entity.amplitude)
            .setTime(m_pObj->getModule<GlobalTime>()->time())
            .setSize(m_entity.matrixSize.x, m_entity.matrixSize.y)
            .start();
        s3d::Graphics2D::DrawTriangles(m_entity.matrixSize.x * m_entity.matrixSize.y * 2);
    }
}