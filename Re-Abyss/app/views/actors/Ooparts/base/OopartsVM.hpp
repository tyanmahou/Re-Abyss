#pragma once
#include <Siv3D/Vector2D.hpp>
#include <abyss/types/Forward.hpp>

#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/EffectEx/EffectEx.hpp>
#include <abyss/utils/IntervalTimer/IntervalTimer.hpp>
#include <abyss/views/Actors/Ooparts/base/IDrawCallbackView.hpp>

namespace abyss::Actor::Ooparts
{
    class OopartsVM
    {
    private:
        std::unique_ptr<IDrawCallbackView> m_drawCallback;

        virtual void drawCharacter(const s3d::Vec2& pos, const s3d::ColorF& color) const = 0;
    protected:
        s3d::Vec2 m_pos{0, 0};
        Forward m_forward{Forward::Right};
        double m_time = 0;
    public:
        OopartsVM();
        virtual ~OopartsVM() = default;

        OopartsVM& setCallback(std::unique_ptr<IDrawCallbackView>&& callback)
        {
            m_drawCallback = std::move(callback);
            return *this;
        }

        OopartsVM& setTime(double time)
        {
            m_time = time;
            return *this;
        }
        double getTime() const
        {
            return m_time;
        }
        OopartsVM& setPos(const s3d::Vec2& pos)
        {
            m_pos = pos;
            return *this;
        }
        OopartsVM& setForward(Forward forward)
        {
            m_forward = forward;
            return *this;
        }
        void draw() const;
    };
}