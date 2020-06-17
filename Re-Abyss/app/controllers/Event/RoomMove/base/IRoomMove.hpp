#pragma once
#include <memory>

#include <Siv3D/Optional.hpp>
#include <Siv3D/Vector2D.hpp>

#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/StopwatchEx/StopwatchEx.hpp>
#include <abyss/controllers/Event/base/IEvent.hpp>

namespace abyss::Event::RoomMove
{
    class IRoomMove : public IEvent
    {
    protected:
        StopwatchEx m_animation;
        double m_animeMilliSec = 0;
    public:
        IRoomMove(double animeMilliSec);
        void init() override final;
        bool update(double dt) override final;;
        void onEnd() override final;

        virtual s3d::Vec2 calcCameraPos() const = 0;
        virtual s3d::Optional<s3d::Vec2> calcPlayerPos() const
        {
            return s3d::none;
        }
        virtual void onMoveEnd() {}

        double elapsed() const;

        bool isActive() const;
        bool isEnd() const;
        void start();
    };
}