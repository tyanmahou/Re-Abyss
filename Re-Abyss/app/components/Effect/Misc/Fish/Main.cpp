#include <abyss/components/Effect/Misc/Fish/Main.hpp>
#include <abyss/commons/Constants.hpp>
#include <abyss/modules/Effect/base/EffectObj.hpp>
#include <abyss/modules/Camera/Camera.hpp>
#include <abyss/modules/Room/RoomManager.hpp>
#include <abyss/views/Effect/Misc/Fish/FishVM.hpp>
#include <Siv3D.hpp>

namespace abyss::Effect::Misc::Fish
{
    Main::Main(EffectObj* pObj, s3d::int32 fishId):
        m_pObj(pObj),
        m_view(std::make_unique<FishVM>(fishId))
    {}
    Main::~Main()
    {}
    void Main::onStart()
    {
        m_lifeTime = m_pObj->find<LifeTime>();
    }
    void Main::onUpdate()
    {
        double dt = m_pObj->deltaTime();
        m_basePos += m_velocity * dt;

        if (this->checkEnd()) {
            m_pObj->destroy();
        }
    }
    bool Main::onDraw(double time)
    {
        auto viewRect = this->viewRect();
        if (!m_pObj->getModule<Camera>()->inScreen(viewRect)) {
            return !m_isEnd;
        }
        // 減算
        ScopedRenderStates2D state(BlendState::Subtractive);

        auto color = m_color;
        color.a *= m_lifeTime->destroyRate();
        m_view
            ->setPos(viewRect.center())
            .setTime(time)
            .draw(color);
        return !m_isEnd;
    }
    Main& Main::setVelocity(const s3d::Vec2& velocity)
    {
        m_velocity = velocity;
        m_view->setForward(velocity.x > 0 ? Forward::Right : Forward::Left);
        return *this;
    }
    Main& Main::setScale(double scale)
    {
        m_view->setScale(scale);
        return *this;
    }
    bool Main::checkEnd()
    {
        return m_isEnd = !this->isInValidRange();
    }

    bool Main::isInArea(const s3d::RectF& area) const
    {
        return area.intersects(this->viewRect());
    }
    bool Main::isInValidRange() const
    {
        auto viewRect = this->viewRect();
        if (auto roomManager = m_pObj->getModule<RoomManager>()) {
            if (roomManager->currentRoom()
                .getRegion()
                .stretched(Constants::GameScreenSize / 2.0)
                .intersects(viewRect)
                ) {
                return true;
            }
            if (auto&& nextRoom = roomManager->nextRoom(); nextRoom) {
                return nextRoom->getRegion()
                    .stretched(Constants::GameScreenSize / 2.0)
                    .intersects(viewRect);
            }
            return false;
        } else {
            return m_pObj->getModule<Camera>()
                ->screenRegion()
                .stretched(Constants::GameScreenSize / 2.0)
                .intersects(viewRect);
        }
    }
    s3d::RectF Main::viewRect() const
    {
        return s3d::RectF(Arg::center = this->parallaxPos(), m_view->size());
    }
    s3d::Vec2 Main::parallaxPos() const
    {
        const auto& cameraPos = m_pObj->getModule<Camera>()->getPos();
        return m_basePos + cameraPos - cameraPos * m_parallax;
    }
}