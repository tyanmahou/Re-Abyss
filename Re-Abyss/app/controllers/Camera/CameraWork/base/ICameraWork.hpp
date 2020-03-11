#pragma once
#include <memory>

#include <Siv3D/Stopwatch.hpp>
#include <Siv3D/Optional.hpp>
#include <Siv3D/Vector2D.hpp>

#include <abyss/commons/Fwd.hpp>

namespace abyss
{
    class ICameraWork
    {
    protected:
        s3d::Stopwatch m_animation;
        double m_animeMilliSec = 0;
    public:
        ICameraWork(double animeMilliSec);
        virtual ~ICameraWork() = default;

        virtual void update() {}
        virtual void draw(const Camera* const) const {}

        virtual s3d::Vec2 calcCameraPos() const = 0;
        virtual s3d::Optional<s3d::Vec2> calcPlayerPos() const;

        bool isEnd() const;
        virtual void onEnd() {}

        double elapsed() const;

    };
}