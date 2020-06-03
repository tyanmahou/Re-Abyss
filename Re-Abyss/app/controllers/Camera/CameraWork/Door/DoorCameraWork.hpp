#pragma once
#include <abyss/controllers/Camera/CameraWork/base/ICameraWork.hpp>

namespace abyss
{
    class DoorCameraWork : public ICameraWork
    {
        std::pair<s3d::Vec2, s3d::Vec2> m_cameraMove;
        std::pair<s3d::Vec2, s3d::Vec2> m_playerMove;
        s3d::Vec2 m_origin;
        std::function<void()> m_fadeInCallback;
        std::function<void()> m_fadeOutCallback;

        enum class State
        {
            FadeIn,
            FadeOut
        }m_state = State::FadeOut;

        std::unique_ptr<DoorCameraWorkView> m_view;
    public:
        DoorCameraWork(
            Manager* pManager,
            const std::pair<s3d::Vec2, s3d::Vec2>& cameraMove,
            const std::pair<s3d::Vec2, s3d::Vec2>& playerMove,
            const s3d::Vec2& origin,
            std::function<void()> fadeInCallback,
            std::function<void()> fadeOutCallback,
            double animeMilliSec
        );

    protected:

        s3d::Vec2 calcCameraPos() const override;
        s3d::Optional<s3d::Vec2> calcPlayerPos() const override;
        void update() override;
        void draw(const CameraView* const) const override;
        void onEnd() override;

    private:
        double fadeIn0_1()const
        {
            return (this->elapsed() - 0.5) / 0.5;
        }
        double fadeOut0_1()const
        {
            return this->elapsed() / 0.5;
        }
        friend class DoorCameraWorkView;
    };
}