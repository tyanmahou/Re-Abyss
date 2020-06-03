#pragma once
#include <memory>

#include <Siv3D/Optional.hpp>
#include <Siv3D/Vector2D.hpp>

#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/StopwatchEx/StopwatchEx.hpp>

namespace abyss
{
    class ICameraWork
    {
    protected:
        StopwatchEx m_animation;
        double m_animeMilliSec = 0;
        Manager* m_pManager = nullptr;
    public:
        ICameraWork(Manager* pManager, double animeMilliSec);
        virtual ~ICameraWork() = default;

        virtual void update() {}
        virtual void draw(const CameraView* const) const {}

        virtual s3d::Vec2 calcCameraPos() const = 0;
        virtual s3d::Optional<s3d::Vec2> calcPlayerPos() const;

        virtual void onStart() {}

        bool isEnd() const;
        virtual void onEnd() {}

        double elapsed() const;

        bool isActive() const;
        void start();
    };
}