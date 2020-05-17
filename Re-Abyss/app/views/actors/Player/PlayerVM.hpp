#pragma once

#include <Siv3D/Vector2D.hpp>
#include <abyss/utils/TexturePacker/TexturePacker.hpp>
#include <abyss/types/Forward.hpp>
#include <abyss/commons/Fwd.hpp>

namespace abyss::Player
{
    class PlayerVM
    {
        TexturePacker m_texture;
        s3d::Vec2 m_pos;
        s3d::Vec2 m_velocity;
        Forward m_forward;
        double m_charge;

        bool m_isDamaging = false;
        Manager* m_pManager = nullptr;
        s3d::ColorF calcColor() const;

    public:
        PlayerVM();

        PlayerVM& setPos(const s3d::Vec2& pos);
        PlayerVM& setVelocity(const s3d::Vec2& v);
        PlayerVM& setForward(const Forward& forward);
        PlayerVM& setCharge(double charge);

        PlayerVM& setIsDamaging(bool isDamaging);
        PlayerVM& setManager(Manager* pManager);


        void drawStateStay() const;
        void drawStateFloat() const;
        void drawStateRun() const;
        void drawStateSwim() const;
        void drawStateDive() const;
        void drawStateDamage() const;
        void drawStateLadder() const;
        void drawStateLadderTop() const;
        void drawStateDoor() const;

        void drawCharge()const;

        void drawLight() const;
    };
}