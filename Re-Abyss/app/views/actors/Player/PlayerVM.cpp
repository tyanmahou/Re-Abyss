#include "PlayerVM.hpp"
#include <Siv3D.hpp>
#include <abyss/commons/Constants.hpp>
#include <abyss/commons/ColorDef.hpp>
#include <abyss/controllers/ActionSystem/ActionSystem.hpp>
#include <abyss/commons/ColorDef.hpp>
#include <abyss/controllers/World/WorldTime.hpp>

namespace 
{
    using namespace abyss;

    ColorF ChargeToColor(double charge)
    {
        if (charge >= Constants::Player::BigCharge) {
            return ColorDef::Shot::BigCharge;
        } else if (charge >= Constants::Player::MediumCharge) {
            return ColorDef::Shot::MediumCharge;
        } else {
            return ColorF(1);
        }
    }
    int32 GetTimeInt32()
    {
        return static_cast<int32>(WorldTime::Time() * 60);
    }
}

namespace abyss
{
    ColorF PlayerVM::calcColor() const
    {
        return ColorDef::OnDamage(m_isDamaging, WorldTime::Time());
    }
    PlayerVM::PlayerVM():
        m_texture(U"resources/images/actors/Player/player.json")
    {}
    PlayerVM& PlayerVM::setPos(const s3d::Vec2& pos)
    {
        m_pos = pos;
        return *this;
    }
    PlayerVM& PlayerVM::setVelocity(const s3d::Vec2& v)
    {
        m_velocity = v;
        return *this;
    }
    PlayerVM& PlayerVM::setForward(const Forward& forward)
    {
        m_forward = forward;
        return *this;
    }
    PlayerVM& PlayerVM::setCharge(double charge)
    {
        m_charge = charge;
        return *this;
    }

    PlayerVM& PlayerVM::setIsDamaging(bool isDamaging)
    {
        m_isDamaging = isDamaging;
        return *this;
    }

    void PlayerVM::drawStateStay() const
    {
        int32 timer = GetTimeInt32();
        bool isRight = m_forward == Forward::Right;

        int32 page = timer % 240 <= 10 ? 1 : 0;
        m_texture(U"player_stay.png", { isRight ? 40 : 0, 80 * page }, { 40, 80 }).drawAt(m_pos, this->calcColor());
    }
    void PlayerVM::drawStateFloat() const
    {
        int32 timer = GetTimeInt32();
        bool isRight = m_forward == Forward::Right;

        double y = 160;
        if (m_velocity.y < -96) {
            y = 0;
        } else if (m_velocity.y < -48) {
            y = 80;
        } else {
            y = 80 * (timer / 30 % 2) + 160;
        }

        m_texture(U"player_float.png", { isRight ? 60 : 0, y }, { 60, 80 }).drawAt(m_pos, this->calcColor());
    }
    void PlayerVM::drawStateRun() const
    {
        bool isRight = m_forward == Forward::Right;

        int32 x = static_cast<int32>(Periodic::Triangle0_1(1.2s, WorldTime::Time()) * 5) * 60;
        m_texture(U"player_run.png", { x, isRight ? 80 : 0 }, { 60, 80 }).drawAt(m_pos, this->calcColor());
    }
    void PlayerVM::drawStateSwim() const
    {
        int32 timer = GetTimeInt32();
        bool isRight = m_forward == Forward::Right;

        double y = 0;
        if (m_velocity.y < -96) {
            y = 160;
        } else if (m_velocity.y < -48) {
            y = 240;
        } else {
            y = 80 * (timer / 30 % 2);
        }
        m_texture(U"player_swim.png", { isRight ? 60 : 0, y }, { 60, 80 }).drawAt(m_pos, this->calcColor());
    }
    void PlayerVM::drawStateDive() const
    {
        int32 timer = GetTimeInt32();
        bool isRight = m_forward == Forward::Right;

        double y = 80 * (timer / 30 % 2);
        m_texture(U"player_dive.png", { isRight ? 60 : 0, y }, { 60, 80 }).drawAt(m_pos, this->calcColor());
    }
    void PlayerVM::drawStateDamage() const
    {
        bool isRight = m_forward == Forward::Right;

        m_texture(U"player_damage.png", { isRight ? 60 : 0, 0 }, { 60, 80 }).drawAt(m_pos, this->calcColor());
    }
    void PlayerVM::drawStateLadder() const
    {
        m_texture(U"player_ladder.png", { 40 * (static_cast<int32>(m_pos.y / 30) % 2), 0 }, { 40, 80 }).drawAt(m_pos, this->calcColor());
    }
    void PlayerVM::drawStateLadderTop() const
    {
        m_texture(U"player_ladder.png", { 80, 0 }, { 40, 80 }).drawAt(m_pos, this->calcColor());
    }
    void PlayerVM::drawStateDoor() const
    {
        m_texture(U"player_door.png", { 40 * static_cast<int32>(Periodic::Sawtooth0_1(1s) * 2), 0 }, { 40, 80 }).drawAt(m_pos, this->calcColor());
    }
    void PlayerVM::drawCharge() const
    {
        if (m_charge <= Constants::Player::SmallCharge) {
            return;
        }
        ScopedRenderStates2D t2d(BlendState::Additive);
        double a = 0.5 * Periodic::Triangle0_1(0.2s, WorldTime::Time());
        
        ColorF color = ::ChargeToColor(m_charge);

        Circle(m_pos, 80 * (1 - Periodic::Sawtooth0_1(0.6s, WorldTime::Time()))).drawFrame(1, 1, color.setA(a));
        double s = 100 * Periodic::Triangle0_1(0.3s, WorldTime::Time());
        RectF({ 0,0,s, s })
            .setCenter(m_pos)
            .rotated(Math::QuarterPi * Periodic::Square0_1(0.6s, WorldTime::Time()))
            .drawFrame(1, 1, color.setA(0.5 - a));

        if (m_charge >= Constants::Player::BigCharge) {
            Circle(m_pos, Periodic::Triangle0_1(0.3s, WorldTime::Time()) * 30 + 30).draw(color.setA(a));
        } else if (m_charge >= Constants::Player::MediumCharge) {
            Circle(m_pos, Periodic::Triangle0_1(0.3s, WorldTime::Time()) * 5 + 30).draw(color.setA(a));
        }
    }
    void PlayerVM::drawLight() const
    {
        ActionSystem::Light()->addLight({ m_pos, 700 });
    }
}
