#pragma once
#include <abyss/modules/Event/RoomMove/base/IRoomMove.hpp>
#include <abyss/components/Actors/Gimmick/Door/DoorProxy.hpp>
#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::ui::Fade::IrisOut
{
    class FadeCtrl;
}
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

        Ref<ui::Fade::IrisOut::FadeCtrl> m_fadeUI;
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
            const Actor::Gimmick::Door::DoorProxy& door,
            const s3d::Vec2& playerPos,
            std::function<void()> fadeInCallback,
            double milliSec = 2000
        );
    protected:
        void onMoveStart() override;
        void onMoveUpdate([[maybe_unused]] double t) override;
        void onMoveEnd() override;

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