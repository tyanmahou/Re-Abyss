#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/Event/RoomMove/IRoomMoveCallback.hpp>
#include <abyss/modules/Fade/Fader.hpp>

namespace abyss::Event::RoomMove::DoorMove
{
    class RoomMoveCallback : public IRoomMoveCallback
    {
        enum class State
        {
            FadeIn,
            FadeOut
        };
    public:
        RoomMoveCallback(
            EventObj* pEvent,
            const std::pair<s3d::Vec2, s3d::Vec2>& cameraMove,
            const std::pair<s3d::Vec2, s3d::Vec2>& playerMove,
            const s3d::Vec2& origin,
            std::function<void()> fadeInCallback
        );

        void onMoveStart() override;
        void onMoveUpdate(double t) override;
        void onMoveEnd() override;

        s3d::Vec2 calcCameraPos() const override;
        s3d::Vec2 calcPlayerPos() const override;

    private:
        EventObj* m_pEvent;
        double m_elapsed = 0.0;
        std::pair<s3d::Vec2, s3d::Vec2> m_cameraMove;
        std::pair<s3d::Vec2, s3d::Vec2> m_playerMove;
        s3d::Vec2 m_origin;
        std::function<void()> m_fadeInCallback;

        std::shared_ptr<Fade::IrisOutFade> m_fade;
        State m_state = State::FadeOut;

        double fadeIn0_1()const
        {
            return (m_elapsed - 0.5) / 0.5;
        }
        double fadeOut0_1()const
        {
            return m_elapsed / 0.5;
        }
    };
}
