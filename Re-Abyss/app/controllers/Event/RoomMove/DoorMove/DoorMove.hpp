#pragma once
#include <abyss/controllers/Event/RoomMove/base/IRoomMove.hpp>

namespace abyss::Event::RoomMove
{
    class DoorMove : public IRoomMove
    {
        std::pair<s3d::Vec2, s3d::Vec2> m_cameraMove;
        std::pair<s3d::Vec2, s3d::Vec2> m_playerMove;
        s3d::Vec2 m_origin;
        std::function<void()> m_fadeInCallback;

        enum class State
        {
            FadeIn,
            FadeOut
        }m_state = State::FadeOut;

        // @todo view
    public:
        DoorMove(
            const std::pair<s3d::Vec2, s3d::Vec2>& cameraMove,
            const std::pair<s3d::Vec2, s3d::Vec2>& playerMove,
            const s3d::Vec2& origin,
            std::function<void()> fadeInCallback,
            double animeMilliSec
        );

        /// <summary>
        /// ドア移動を開始
        /// </summary>
        /// <param name="door"></param>
        /// <param name="playerPos"></param>
        /// <param name="fadeInCallback"></param>
        /// <param name="milliSec"></param>
        /// <returns></returns>
        static bool Start(
            const Door::DoorActor& door,
            const s3d::Vec2& playerPos,
            std::function<void()> fadeInCallback,
            double milliSec = 2000
        );
    protected:
        void onMoveUpdate([[maybe_unused]] double t) override;
        s3d::Vec2 calcCameraPos() const override;
        s3d::Vec2 calcPlayerPos() const override;
    private:
        double fadeIn0_1()const
        {
            return (this->elapsed() - 0.5) / 0.5;
        }
        double fadeOut0_1()const
        {
            return this->elapsed() / 0.5;
        }
    };
}