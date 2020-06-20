#include "DoorMove.hpp"
#include <Siv3D.hpp>
#include <abyss/controllers/Manager/Manager.hpp>

#include <abyss/controllers/Camera/Camera.hpp>
#include <abyss/controllers/Event/Events.hpp>
#include <abyss/controllers/Actors/Gimmick/Door/DoorActor.hpp>

#include <abyss/controllers/UI/UI.hpp>
#include <abyss/controllers/UI/Fade/SmoothCircle/SmoothCircle.hpp>

namespace abyss::Event::RoomMove
{
    bool DoorMove::Start(const Door::DoorActor& door, const s3d::Vec2& playerPos, std::function<void()> fadeInCallback, double milliSec)
    {
        assert(milliSec > 0);
        auto camera = door.getModule<Camera>();

        const auto& nextRoom = door.getNextRoom();
        camera->setNextRoom(nextRoom);

        const auto& current = camera->getCurrentRoom();
        Vec2 playerFrom = door.fixedVisiterPos();
        Vec2 playerTo = door.getTargetPos();
        Vec2 from = current.cameraBorderAdjusted(playerFrom);
        Vec2 to = nextRoom.cameraBorderAdjusted(playerTo);

        auto event = std::make_shared<DoorMove>(
            std::make_pair(from, to),
            std::make_pair(playerFrom, playerTo),
            playerPos,
            fadeInCallback,
            milliSec
            );

        door.getModule<Events>()->regist(event);

        return true;
    }

    DoorMove::DoorMove(
        const std::pair<s3d::Vec2, s3d::Vec2>& cameraMove,
        const std::pair<s3d::Vec2, s3d::Vec2>& playerMove,
        const s3d::Vec2& origin,
        std::function<void()> fadeInCallback,
        double animeMilliSec
    ):
        IRoomMove(animeMilliSec),
        m_cameraMove(cameraMove),
        m_playerMove(playerMove),
        m_origin(origin),
        m_fadeInCallback(fadeInCallback)
    {}

    void DoorMove::onMoveStart()
    {
        m_fadeUI = m_pManager->getModule<UI>()->create<ui::Fade::SmoothCircle>();
    }

    void DoorMove::onMoveUpdate(double t)
    {
        if (m_state == State::FadeOut) {
            if (t >= 0.5) {
                m_state = State::FadeIn;
                if (this->m_fadeInCallback) {
                    this->m_fadeInCallback();
                }
            }
        }

        bool isFadeOut = m_state == State::FadeOut;

        if (auto ui = m_fadeUI) {
            auto pos = isFadeOut ? m_playerMove.first : m_playerMove.second;
            ui->setPos(pos)
                .setFadeTime(isFadeOut ? this->fadeOut0_1() : this->fadeIn0_1())
                .setIsFadeOut(isFadeOut)
                ;
        }
    }
    void DoorMove::onMoveEnd()
    {
        if (auto ui = m_fadeUI) {
            ui->destroy();
        }
    }

    s3d::Vec2 DoorMove::calcCameraPos() const
    {
        return m_state == State::FadeOut ?
            m_cameraMove.first
            : m_cameraMove.second;
    }
    s3d::Vec2 DoorMove::calcPlayerPos() const
    {
        return m_state == State::FadeOut ?
            EaseOut(Easing::Circ, m_origin, m_playerMove.first, Min(1.0, this->fadeOut0_1() * 1.5))
            : m_playerMove.second;
    }
}
