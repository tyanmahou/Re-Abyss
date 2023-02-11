#pragma once
#include <Siv3D/Vector2D.hpp>
#include <abyss/utils/TexturePacker/TexturePacker.hpp>
#include <abyss/values/Forward.hpp>
#include <abyss/commons/Fwd.hpp>
#include <abyss/views/Actor/Ooparts/base/OopartsView.hpp>
#include <abyss/views/Actor/Player/Xto/XtoAtkVM.hpp>
#include <abyss/views/Actor/Player/Motion.hpp>

namespace abyss::Actor::Player
{
    class PlayerVM
    {
        friend class MotionUtil;
    public:
        PlayerVM();

        PlayerVM& setTime(double time);
        PlayerVM& setPos(const s3d::Vec2& pos);
        PlayerVM& setVelocity(const s3d::Vec2& v);
        PlayerVM& setForward(const Forward& forward);
        PlayerVM& setCharge(double charge);

        PlayerVM& setIsAttacking(bool isAttacking);

        PlayerVM& setMotion(Motion motion)
        {
            m_motion = motion;
            return *this;
        }

        PlayerVM& setAnimeTime(double animeTime)
        {
            m_animeTime = animeTime;
            return *this;
        }
        PlayerVM& setColorMul(const s3d::ColorF color);
        void draw() const;
    private:
        void drawStateStay() const;
        void drawStateStayAtk() const;
        void drawStateFloat() const;
        void drawStateFloatAtk() const;
        void drawStateRun() const;
        void drawStateRunAtk() const;
        void drawStateSwim() const;
        void drawStateSwimAtk() const;
        void drawStateDive() const;
        void drawStateDiveAtk() const;
        void drawStateDamage() const;
        void drawStateDead(double rate) const;
        void drawStateLadder() const;
        void drawStateLadderAtk() const;
        void drawStateLadderTop() const;
        void drawStateLadderTopAtk() const;
        void drawStateDoor() const;

        void drawCharge()const;
        s3d::ColorF calcColor() const;
    private:
        TexturePacker m_texture;
        s3d::Vec2 m_pos;
        s3d::Vec2 m_velocity;
        Forward m_forward;
        double m_charge = 0;

        bool m_isAttacking = false;
        double m_time = 0;
        Motion m_motion;
        double m_animeTime = 0;
        s3d::ColorF m_colorMul;
    };
}
