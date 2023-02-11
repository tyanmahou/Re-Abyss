#include <abyss/views/Actor/Player/PlayerVM.hpp>

#include <Siv3D.hpp>
#include <abyss/commons/ColorDef.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <abyss/params/Actor/Player/Param.hpp>
#include <abyss/params/Actor/Player/ShotParam.hpp>
#include <abyss/views/Actor/Player/MotionUtil.hpp>

namespace
{
    using namespace abyss;

    ColorF ChargeToColor(double charge)
    {
        if (charge >= Actor::Player::ShotParam::Big::Charge) {
            return ColorDef::Shot::BigCharge;
        } else if (charge >= Actor::Player::ShotParam::Medium::Charge) {
            return ColorDef::Shot::MediumCharge;
        } else {
            return ColorF(1);
        }
    }
}

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
    PlayerVM& PlayerVM::setCharge(double charge)
    {
        m_charge = charge;
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
        this->drawCharge();
    }

    void PlayerVM::drawStateStay() const
    {
        if (m_isAttacking) {
            this->drawStateStayAtk();
            return;
        }
        m_texture(U"stay")(MotionUtil::StayRect(this))
            .drawAt(m_pos, this->calcColor());
    }
    void PlayerVM::drawStateStayAtk() const
    {
        m_texture(U"stay_atk")(MotionUtil::StayAtkRect(this))
            .drawAt(m_pos, this->calcColor());
    }
    void PlayerVM::drawStateFloat() const
    {
        if (m_isAttacking) {
            this->drawStateFloatAtk();
            return;
        }
        m_texture(U"float")(MotionUtil::FloatRect(this))
            .drawAt(m_pos, this->calcColor());
    }
    void PlayerVM::drawStateFloatAtk() const
    {
        m_texture(U"float_atk")(MotionUtil::FloatAtkRect(this))
            .drawAt(m_pos, this->calcColor());
    }
    void PlayerVM::drawStateRun() const
    {
        if (m_isAttacking) {
            this->drawStateRunAtk();
            return;
        }
        m_texture(U"run")(MotionUtil::RunRect(this))
            .drawAt(m_pos, this->calcColor());
    }
    void PlayerVM::drawStateRunAtk() const
    {
        m_texture(U"run_atk")(MotionUtil::RunAtkRect(this))
            .drawAt(m_pos, this->calcColor());
    }
    void PlayerVM::drawStateSwim() const
    {
        if (m_isAttacking) {
            this->drawStateSwimAtk();
            return;
        }
        m_texture(U"swim")(MotionUtil::SwimRect(this))
            .drawAt(m_pos, this->calcColor());
    }
    void PlayerVM::drawStateSwimAtk() const
    {

        m_texture(U"swim_atk")(MotionUtil::SwimAtkRect(this))
            .drawAt(m_pos, this->calcColor());
    }
    void PlayerVM::drawStateDive() const
    {
        if (m_isAttacking) {
            this->drawStateDiveAtk();
            return;
        }

        m_texture(U"dive")(MotionUtil::DiveRect(this))
            .drawAt(m_pos, this->calcColor());
    }
    void PlayerVM::drawStateDiveAtk() const
    {
        m_texture(U"dive_atk")(MotionUtil::DiveAtkRect(this))
            .drawAt(m_pos, this->calcColor());
    }
    void PlayerVM::drawStateDamage() const
    {
        m_texture(U"damage")(MotionUtil::DamageRect(this))
            .drawAt(m_pos, this->calcColor());
    }
    void PlayerVM::drawStateDead() const
    {
        Vec2 pos;
        m_texture(U"dead")(MotionUtil::DeadRect(this, &pos))
            .drawAt(pos, this->calcColor());
    }
    void PlayerVM::drawStateLadder() const
    {
        if (m_isAttacking) {
            this->drawStateLadderAtk();
            return;
        }
        m_texture(U"ladder")(MotionUtil::LadderRect(this))
            .drawAt(m_pos, this->calcColor());
    }
    void PlayerVM::drawStateLadderAtk() const
    {
        m_texture(U"ladder_atk")(MotionUtil::LadderAtkRect(this))
            .drawAt(m_pos, this->calcColor());
    }
    void PlayerVM::drawStateLadderTop() const
    {
        if (m_isAttacking) {
            this->drawStateLadderTopAtk();
            return;
        }
        m_texture(U"ladder")(MotionUtil::LadderTopRect(this))
            .drawAt(m_pos, this->calcColor());
    }
    void PlayerVM::drawStateLadderTopAtk() const
    {
        m_texture(U"ladder_atk")(MotionUtil::LadderTopAtkRect(this))
            .drawAt(m_pos, this->calcColor());
    }
    void PlayerVM::drawStateDoor() const
    {
        m_texture(U"door")(MotionUtil::DoorRect(this))
            .drawAt(m_pos, this->calcColor());
    }
    void PlayerVM::drawCharge() const
    {
        if (m_charge <= ShotParam::Small::Charge) {
            return;
        }
        ScopedRenderStates2D t2d(BlendState::Additive);
        double a = 0.5 * Periodic::Triangle0_1(0.2s, m_time);
        
        ColorF color = ::ChargeToColor(m_charge);

        Circle(m_pos, 80 * (1 - Periodic::Sawtooth0_1(0.6s, m_time))).drawFrame(1, 1, color.setA(a));
        double s = 100 * Periodic::Triangle0_1(0.3s, m_time);
        RectF({ 0,0,s, s })
            .setCenter(m_pos)
            .rotated(Math::QuarterPi * Periodic::Square0_1(0.6s, m_time))
            .drawFrame(1, 1, color.setA(0.5 - a));

        if (m_charge >= ShotParam::Big::Charge) {
            Circle(m_pos, Periodic::Triangle0_1(0.3s, m_time) * 30 + 30).draw(color.setA(a));
        } else if (m_charge >= ShotParam::Medium::Charge) {
            Circle(m_pos, Periodic::Triangle0_1(0.3s, m_time) * 5 + 30).draw(color.setA(a));
        }
    }
}
