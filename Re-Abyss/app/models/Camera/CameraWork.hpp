#pragma once
#include <Siv3D/Stopwatch.hpp>
#include <Siv3D/Optional.hpp>
#include <Siv3D/Vector2D.hpp>
#include <memory>

namespace abyss
{
    class CameraModel;
    class RoomModel;
    class DoorModel;

    class ICameraWork
    {
    protected:
        s3d::Stopwatch m_animation;
        double m_animeMilliSec = 0;
    public:
        ICameraWork(double animeMilliSec);
        virtual ~ICameraWork() = default;

        virtual void update() {}
        virtual s3d::Vec2 calcCameraPos() const = 0;
        virtual s3d::Optional<s3d::Vec2> calcPlayerPos() const;

        bool isEnd() const;
        virtual void onEnd() {}

        double elapsed() const;
    };

    class RoomMoveCameraWork : public ICameraWork
    {
        std::pair<s3d::Vec2, s3d::Vec2> m_cameraMove;
        std::pair<s3d::Vec2, s3d::Vec2> m_playerMove;
        std::function<void()> m_callback;
    public:
        RoomMoveCameraWork(
            const std::pair<s3d::Vec2, s3d::Vec2>& cameraMove,
            const std::pair<s3d::Vec2, s3d::Vec2>& playerMove,
            std::function<void()> callback,
            double animeMilliSec
        );
        static std::shared_ptr<RoomMoveCameraWork> Create(
            const CameraModel& camera,
            const s3d::Vec2& playerPos,
            std::function<void()> callback,
            double milliSec
        );
    protected:
        s3d::Vec2 calcCameraPos() const override;
        s3d::Optional<s3d::Vec2> calcPlayerPos() const override;

        void onEnd() override;
    };

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
    public:
        DoorCameraWork(
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