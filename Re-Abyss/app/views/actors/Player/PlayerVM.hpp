#pragma once

#include <Siv3D/Vector2D.hpp>
#include <abyss/utils/TexturePacker/TexturePacker.hpp>
#include <abyss/types/Forward.hpp>
#include <abyss/commons/Fwd.hpp>
#include <abyss/views/Actors/Ooparts/base/OopartsView.hpp>
#include <abyss/views/Actors/Player/Xto/XtoAtkVM.hpp>

namespace abyss::Actor::Player
{
    class PlayerVM
    {
    private:
        TexturePacker m_texture;
        s3d::Vec2 m_pos;
        s3d::Vec2 m_velocity;
        Forward m_forward;
        double m_charge;

        bool m_isAttacking = false;
        bool m_isDamaging = false;
        double m_time = 0;

        s3d::ColorF calcColor() const;

        std::unique_ptr<Ooparts::OopartsView> m_oopartsView;
        std::shared_ptr<XtoAtkVM> m_xto;
    public:
        PlayerVM();
        PlayerVM& setOopartsView(std::unique_ptr<Ooparts::OopartsView>&& ooparts);
        PlayerVM& setXtoAtkView(std::shared_ptr<XtoAtkVM>&& xto);

        PlayerVM& setTime(double time);
        PlayerVM& setPos(const s3d::Vec2& pos);
        PlayerVM& setVelocity(const s3d::Vec2& v);
        PlayerVM& setForward(const Forward& forward);
        PlayerVM& setCharge(double charge);

        PlayerVM& setIsAttacking(bool isAttacking);
        PlayerVM& setIsDamaging(bool isDamaging);
        PlayerVM& setManager(Manager* pManager);


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
    };
}