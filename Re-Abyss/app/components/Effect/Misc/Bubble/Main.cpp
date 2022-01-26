#include <abyss/components/Effect/Misc/Bubble/Main.hpp>
#include <abyss/commons/Constants.hpp>
#include <abyss/modules/Effect/base/EffectObj.hpp>
#include <abyss/modules/Camera/Camera.hpp>
#include <abyss/modules/Room/RoomManager.hpp>
#include <abyss/modules/Light/Light.hpp>
#include <Siv3D.hpp>

namespace abyss::Effect::Misc::Bubble
{
    Main::Main(EffectObj* pObj):
        m_pObj(pObj)
    {}
    void Main::onStart()
    {
        m_lifeTime = m_pObj->find<LifeTime>();
    }
    void Main::onUpdate()
    {
        auto time = m_pObj->timeSec();
        m_basePos += m_velocity * m_pObj->deltaTime();
        m_pos = m_basePos + Vec2{ m_deflection * Sin(time), 0.0 };
        m_radius = Min(m_maxRadius, EaseOut(Easing::Cubic, 0.0, m_maxRadius, time));

        if (this->checkEnd()) {
            m_pObj->destroy();
        }
    }
   bool Main::onDraw(double time)
    {
        const Circle circle = this->drawCircle();
        if (!m_pObj->getModule<Camera>()->inScreen(circle)) {
            return !m_isEnd;
        }
        ScopedRenderStates2D state(BlendState::Additive);

        // Color
        ColorF color = m_kind == BubbleKind::Big ?
            m_color :
            m_color * Periodic::Sine0_1(Math::TwoPi, time);
        color.a *= m_lifeTime->destroyRate();
        circle.draw(color);

        // Light
        if (m_kind == BubbleKind::Small) {
            if (auto* light = m_pObj->getModule<Light>()) {
                light->addCircle(circle.center, circle.r, color.a);
            }
        }
        return !m_isEnd;
    }

    bool Main::checkEnd()
    {
        return m_isEnd = !this->isInValidRange(parallaxPos());
    }
    bool Main::isInArea(const s3d::RectF& area) const
    {
        return area.intersects(this->drawCircle());
    }
    s3d::Vec2 Main::parallaxPos() const
    {
        const auto& cameraPos = m_pObj->getModule<Camera>()->getPos();
        return m_pos + cameraPos - cameraPos * m_parallax;
    }
    s3d::Circle Main::drawCircle() const
    {
        return s3d::Circle(this->parallaxPos(), m_radius);
    }
    bool Main::isInValidRange(const s3d::Vec2& pos) const
    {
        if (m_area.intersects(pos)) {
            return true;
        }
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
    }
}