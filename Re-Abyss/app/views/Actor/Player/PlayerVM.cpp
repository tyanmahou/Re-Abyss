#include <abyss/views/Actor/Player/PlayerVM.hpp>

#include <Siv3D.hpp>
#include <abyss/commons/ColorDef.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <abyss/views/Actor/Player/MotionUtil.hpp>

namespace abyss::Actor::Player
{
    ColorF PlayerVM::calcColor() const
    {
        return m_colorMul;
    }
    PlayerVM::PlayerVM():
        m_texture(Resource::Assets::Main()->load(U"Actor/Player/Player.json")),
        m_colorMul(s3d::Palette::White)
    {}
    PlayerVM& PlayerVM::setTime(double time)
    {
        m_time = time;
        return *this;
    }
    PlayerVM& PlayerVM::setPos(const s3d::Vec2& pos)
    {
        m_pos = s3d::Round(pos);
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
    PlayerVM& PlayerVM::setIsAttacking(bool isAttacking)
    {
        m_isAttacking = isAttacking;
        return *this;
    }

    PlayerVM& PlayerVM::setColorMul(const s3d::ColorF color)
    {
        m_colorMul = color;
        return *this;
    }

    void PlayerVM::draw() const
    {
        switch (m_motion) {
        case Motion::Stay:
            this->drawStateStay();
            break;
        case Motion::Float:
            this->drawStateFloat();
            break;
        case Motion::Run:
            this->drawStateRun();
            break;
        case Motion::Swim:
            this->drawStateSwim();
            break;
        case Motion::Dive:
            this->drawStateDive();
            break;
        case Motion::Damage:
            this->drawStateDamage();
            break;
        case Motion::Dead:
            this->drawStateDead();
            break;
        case Motion::Ladder:
            this->drawStateLadder();
            break;
        case Motion::LadderTop:
            this->drawStateLadderTop();
            break;
        case Motion::Door:
            this->drawStateDoor();
            break;
        }
    }

    void PlayerVM::drawStateStay() const
    {
        if (m_isAttacking) {
            this->drawStateStayAtk();
            return;
        }
        m_texture(U"stay")(MotionUtil::StayRect(this))
            .draw(Arg::bottomCenter = m_pos, this->calcColor());
    }
    void PlayerVM::drawStateStayAtk() const
    {
        m_texture(U"stay_atk")(MotionUtil::StayAtkRect(this))
            .draw(Arg::bottomCenter = m_pos, this->calcColor());
    }
    void PlayerVM::drawStateFloat() const
    {
        if (m_isAttacking) {
            this->drawStateFloatAtk();
            return;
        }
        m_texture(U"float")(MotionUtil::FloatRect(this))
            .draw(Arg::bottomCenter = m_pos, this->calcColor());
    }
    void PlayerVM::drawStateFloatAtk() const
    {
        m_texture(U"float_atk")(MotionUtil::FloatAtkRect(this))
            .draw(Arg::bottomCenter = m_pos, this->calcColor());
    }
    void PlayerVM::drawStateRun() const
    {
        if (m_isAttacking) {
            this->drawStateRunAtk();
            return;
        }
        m_texture(U"run")(MotionUtil::RunRect(this))
            .draw(Arg::bottomCenter = m_pos, this->calcColor());
    }
    void PlayerVM::drawStateRunAtk() const
    {
        m_texture(U"run_atk")(MotionUtil::RunAtkRect(this))
            .draw(Arg::bottomCenter = m_pos, this->calcColor());
    }
    void PlayerVM::drawStateSwim() const
    {
        if (m_isAttacking) {
            this->drawStateSwimAtk();
            return;
        }
        m_texture(U"swim")(MotionUtil::SwimRect(this))
            .draw(Arg::bottomCenter = m_pos, this->calcColor());
    }
    void PlayerVM::drawStateSwimAtk() const
    {

        m_texture(U"swim_atk")(MotionUtil::SwimAtkRect(this))
            .draw(Arg::bottomCenter = m_pos, this->calcColor());
    }
    void PlayerVM::drawStateDive() const
    {
        if (m_isAttacking) {
            this->drawStateDiveAtk();
            return;
        }

        m_texture(U"dive")(MotionUtil::DiveRect(this))
            .draw(Arg::bottomCenter = m_pos, this->calcColor());
    }
    void PlayerVM::drawStateDiveAtk() const
    {
        m_texture(U"dive_atk")(MotionUtil::DiveAtkRect(this))
            .draw(Arg::bottomCenter = m_pos, this->calcColor());
    }
    void PlayerVM::drawStateDamage() const
    {
        m_texture(U"damage")(MotionUtil::DamageRect(this))
            .draw(Arg::bottomCenter = m_pos, this->calcColor());
    }
    void PlayerVM::drawStateDead() const
    {
        Vec2 pos;
        m_texture(U"dead")(MotionUtil::DeadRect(this, &pos))
            .draw(Arg::bottomCenter = m_pos, this->calcColor());
    }
    void PlayerVM::drawStateLadder() const
    {
        if (m_isAttacking) {
            this->drawStateLadderAtk();
            return;
        }
        m_texture(U"ladder")(MotionUtil::LadderRect(this))
            .draw(Arg::bottomCenter = m_pos, this->calcColor());
    }
    void PlayerVM::drawStateLadderAtk() const
    {
        m_texture(U"ladder_atk")(MotionUtil::LadderAtkRect(this))
            .draw(Arg::bottomCenter = m_pos, this->calcColor());
    }
    void PlayerVM::drawStateLadderTop() const
    {
        if (m_isAttacking) {
            this->drawStateLadderTopAtk();
            return;
        }
        m_texture(U"ladder")(MotionUtil::LadderTopRect(this))
            .draw(Arg::bottomCenter = m_pos, this->calcColor());
    }
    void PlayerVM::drawStateLadderTopAtk() const
    {
        m_texture(U"ladder_atk")(MotionUtil::LadderTopAtkRect(this))
            .draw(Arg::bottomCenter = m_pos, this->calcColor());
    }
    void PlayerVM::drawStateDoor() const
    {
        m_texture(U"door")(MotionUtil::DoorRect(this))
            .draw(Arg::bottomCenter = m_pos, this->calcColor());
    }
}
