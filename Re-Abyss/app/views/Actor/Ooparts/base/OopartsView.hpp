#pragma once
#include <Siv3D/Vector2D.hpp>
#include <abyss/types/Forward.hpp>

#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/EffectEx/EffectEx.hpp>
#include <abyss/utils/IntervalTimer/IntervalTimer.hpp>
#include <abyss/views/Actor/Ooparts/base/IDrawCallbackView.hpp>
#include <abyss/views/Actor/Ooparts/base/BaseVM.hpp>

namespace abyss::Actor::Ooparts
{
    class OopartsView
    {
    private:
        std::shared_ptr<IDrawCallbackView> m_drawCallback;
        std::shared_ptr<BaseVM> m_character;

        s3d::Vec2 m_pos{0, 0};
        Forward m_forward{Forward::Right};
        double m_time = 0;

        IntervalTimer m_effectTimer;
    public:
        OopartsView();
        virtual ~OopartsView() = default;

        OopartsView& setCallback(const std::shared_ptr<IDrawCallbackView>& callback)
        {
            m_drawCallback = callback;
            return *this;
        }

        OopartsView& setCharacter(const std::shared_ptr<BaseVM>& character)
        {
            m_character = character;
            return *this;
        }

        OopartsView& setTime(double time)
        {
            m_time = time;
            return *this;
        }
        double getTime() const
        {
            return m_time;
        }
        OopartsView& setPos(const s3d::Vec2& pos)
        {
            m_pos = pos;
            return *this;
        }
        OopartsView& setForward(Forward forward)
        {
            m_forward = forward;
            return *this;
        }
        void draw() const;
    };
}