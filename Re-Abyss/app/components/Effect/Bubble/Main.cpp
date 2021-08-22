#pragma once
#include "Main.hpp"
#include <abyss/commons/Constants.hpp>
#include <abyss/modules/Effect/base/EffectObj.hpp>
#include <abyss/modules/Camera/Camera.hpp>
#include <abyss/modules/Room/RoomManager.hpp>
#include <abyss/modules/Light/Light.hpp>

#include <Siv3D.hpp>

namespace abyss::Effect::Bubble
{
    Main::Main(EffectObj* pObj):
        m_pObj(pObj)
    {}
    void Main::onUpdate()
    {
        m_basePos += m_velocity * m_pObj->deltaTime();
        m_pos = m_basePos + Vec2{ m_deflection * Sin(m_pObj->updateTimeSec()), 0.0 };

        if (this->checkEnd()) {
            m_pObj->destroy();
        }
    }
    void Main::onDraw(double time)
    {
        ScopedRenderStates2D state(BlendState::Additive);

        // Color
        ColorF color = m_kind == BubbleKind::Big ?
            m_color :
            m_color * Periodic::Sine0_1(Math::TwoPi, time);

        const Circle circle = this->drawCircle(time);
        circle.draw(color);

        // Light
        if (m_kind == BubbleKind::Small) {
            if (auto* light = m_pObj->getModule<Light>()) {
                light->addCircle(circle.center, circle.r, color.a);
            }
        }
    }

    bool Main::checkEnd()
    {
        return m_isEnd = !this->isInValidRange(parallaxPos());
    }
    s3d::Vec2 Main::parallaxPos() const
    {
        const auto& cameraPos = m_pObj->getModule<Camera>()->getPos();
        return m_pos + cameraPos - cameraPos * m_parallax;
    }
    s3d::Circle Main::drawCircle(double time) const
    {
        const double r = Min(m_maxRadius, EaseOut(Easing::Cubic, 0.0, m_maxRadius, time));
        return s3d::Circle(this->parallaxPos(), r);
    }
    bool Main::isInValidRange(const s3d::Vec2& pos) const
    {
        if (auto roomManager = m_pObj->getModule<RoomManager>()) {
            if (roomManager->currentRoom()
                .getRegion()
                .stretched(Constants::GameScreenSize / 2.0)
                .intersects(pos)
                ) {
                return true;
            }
            if (auto&& nextRoom = roomManager->nextRoom(); nextRoom) {
                return nextRoom->getRegion()
                    .stretched(Constants::GameScreenSize / 2.0)
                    .intersects(pos);
            }
            return false;
        } else {
            return m_pObj->getModule<Camera>()
                ->screenRegion()
                .stretched(Constants::GameScreenSize / 2.0)
                .intersects(pos);
        }
        return false;
    }
}