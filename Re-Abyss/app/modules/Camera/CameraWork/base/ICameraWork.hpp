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
        ICameraWork(double animeMilliSec);
        virtual ~ICameraWork() = default;

        void setManager(Manager* pManager)
        {
            m_pManager = pManager;
        }
        virtual void update() {}

        virtual s3d::Vec2 calcCameraPos() const = 0;

        virtual void onStart() {}

        bool isEnd() const;
        virtual void onEnd() {}

        double elapsed() const;

        bool isActive() const;
        void start();
    };
}