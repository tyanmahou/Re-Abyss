#include "PlayerVM.hpp"
#include <Siv3D.hpp>
#include <abyss/commons/ColorDef.hpp>
#include <abyss/modules/System/System.hpp>
#include <abyss/commons/ColorDef.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <abyss/params/Actors/Player/Param.hpp>
#include <abyss/params/Actors/Player/ShotParam.hpp>

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
    int32 GetTimeInt32(double time)
    {
        return static_cast<int32>(time * 60);
    }
}

namespace abyss::Actor::Player
{
    ColorF PlayerVM::calcColor() const
    {
        return ColorDef::OnDamage(m_isDamaging, m_time);
    }
    PlayerVM::PlayerVM():
        m_texture(Resource::Assets::Main()->loadTexturePacker(U"actors/Player/player.json"))
    {}
    PlayerVM& PlayerVM::setOopartsView(std::unique_ptr<Ooparts::OopartsView> && ooparts)
    {
        m_oopartsView = std::move(ooparts);
        return *this;
    }
    PlayerVM& PlayerVM::setXtoAtkView(std::shared_ptr<XtoAtkVM> && xto)
    {
        m_xto = xto;
        return *this;
    }
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

    PlayerVM& PlayerVM::setIsDamaging(bool isDamaging)
    {
        m_isDamaging = isDamaging;
        return *this;
    }

    void PlayerVM::drawStateStay() const
    {
        if (m_isAttacking) {
            this->drawStateStayAtk();
            return;
        }
        int32 timer = GetTimeInt32(m_time);
        bool isRight = m_forward == Forward::Right;

        int32 page = timer % 240 <= 10 ? 1 : 0;
        m_texture(U"stay")({ isRight ? 40 : 0, 80 * page }, { 40, 80 }).drawAt(m_pos, this->calcColor());
    }
    void PlayerVM::drawStateStayAtk() const
    {
        auto drawer = [this]() {
            bool isRight = m_forward == Forward::Right;
            m_texture(U"stay_atk")({ 0, isRight ? 80 : 0 }, { 80, 80 })
                .drawAt(m_pos, this->calcColor());
        };
        m_xto->setDrawFunc(drawer);
        m_oopartsView
            ->setCharacter(m_xto)
            .setTime(m_time)
            .setForward(m_forward)
            .setPos(m_pos + s3d::Vec2{23 * m_forward, -2 })
            .draw();
    }
    void PlayerVM::drawStateFloat() const
    {
        if (m_isAttacking) {
            this->drawStateFloatAtk();
            return;
        }
        int32 timer = GetTimeInt32(m_time);
        bool isRight = m_forward == Forward::Right;

        double y = 160;
        if (m_velocity.y < -96) {
            y = 0;
        } else if (m_velocity.y < -48) {
            y = 80;
        } else {
            y = 80 * (timer / 30 % 2) + 160;
        }

        m_texture(U"float")({ isRight ? 60 : 0, y }, { 60, 80 }).drawAt(m_pos, this->calcColor());
    }
    void PlayerVM::drawStateFloatAtk() const
    {
        auto drawer = [this]() {
            int32 timer = GetTimeInt32(m_time);
            bool isRight = m_forward == Forward::Right;

            double y = 80 * (timer / 30 % 2);
            m_texture(U"float_atk")({ isRight ? 70 : 0, y }, { 70, 80 }).drawAt(m_pos, this->calcColor());
        };
        m_xto->setDrawFunc(drawer);
        m_oopartsView
            ->setCharacter(m_xto)
            .setTime(m_time)
            .setForward(m_forward)
            .setPos(m_pos + s3d::Vec2{ 26 * m_forward, -4 })
            .draw();
    }
    void PlayerVM::drawStateRun() const
    {
        if (m_isAttacking) {
            this->drawStateRunAtk();
            return;
        }
        bool isRight = m_forward == Forward::Right;

        int32 x = static_cast<int32>(Periodic::Triangle0_1(1.2s, m_time) * 5) * 60;
        m_texture(U"run")({ x, isRight ? 80 : 0 }, { 60, 80 }).drawAt(m_pos, this->calcColor());
    }
    void PlayerVM::drawStateRunAtk() const
    {
        auto drawer = [this]() {
            bool isRight = m_forward == Forward::Right;
            auto page = static_cast<int32>(Periodic::Triangle0_1(1.2s, m_time) * 5);
            if (page == 3) {
                page = 1;
            } else if (page == 4) {
                page = 0;
            }
            int32 x = page * 80;
            m_texture(U"run_atk")({ x, isRight ? 80 : 0 }, { 80, 80 }).drawAt(m_pos, this->calcColor());
        };
        m_xto->setDrawFunc(drawer);
        m_oopartsView
            ->setCharacter(m_xto)
            .setTime(m_time)
            .setForward(m_forward)
            .setPos(m_pos + s3d::Vec2{ 30 * m_forward, -3 })
            .draw();
    }
    void PlayerVM::drawStateSwim() const
    {
        if (m_isAttacking) {
            this->drawStateSwimAtk();
            return;
        }
        int32 timer = GetTimeInt32(m_time);
        bool isRight = m_forward == Forward::Right;

        double y = 0;
        if (m_velocity.y < -96) {
            y = 160;
        } else if (m_velocity.y < -48) {
            y = 240;
        } else {
            y = 80 * (timer / 30 % 2);
        }
        m_texture(U"swim")({ isRight ? 60 : 0, y }, { 60, 80 }).drawAt(m_pos, this->calcColor());
    }
    void PlayerVM::drawStateSwimAtk() const
    {
        auto drawer = [this]() {
            int32 timer = GetTimeInt32(m_time);
            bool isRight = m_forward == Forward::Right;
            m_texture(U"swim_atk")({ isRight ? 80 : 0, 80 * (timer / 30 % 2) }, { 80, 80 }).drawAt(m_pos, this->calcColor());
        };
        m_xto->setDrawFunc(drawer);
        m_oopartsView
            ->setCharacter(m_xto)
            .setTime(m_time)
            .setForward(m_forward)
            .setPos(m_pos + s3d::Vec2{ 30 * m_forward, -3 })
            .draw();
    }
    void PlayerVM::drawStateDive() const
    {
        if (m_isAttacking) {
            this->drawStateDiveAtk();
            return;
        }
        int32 timer = GetTimeInt32(m_time);
        bool isRight = m_forward == Forward::Right;

        double y = 80 * (timer / 30 % 2);
        m_texture(U"dive")({ isRight ? 60 : 0, y }, { 60, 80 }).drawAt(m_pos, this->calcColor());
    }
    void PlayerVM::drawStateDiveAtk() const
    {
        auto drawer = [this]() {
            int32 timer = GetTimeInt32(m_time);
            bool isRight = m_forward == Forward::Right;

            double y = 80 * (timer / 30 % 2);
            m_texture(U"dive_atk")({ isRight ? 80 : 0, y }, { 80, 80 }).drawAt(m_pos, this->calcColor());
        };
        double offsetX = m_forward == Forward::Right ? 22 : -21;
        m_xto->setDrawFunc(drawer);
        m_oopartsView
            ->setCharacter(m_xto)
            .setTime(m_time)
            .setForward(m_forward)
            .setPos(m_pos + s3d::Vec2{ offsetX, -3 })
            .draw();

    }
    void PlayerVM::drawStateDamage() const
    {
        bool isRight = m_forward == Forward::Right;

        m_texture(U"damage")({ isRight ? 60 : 0, 0 }, { 60, 80 }).drawAt(m_pos, this->calcColor());
    }
    void PlayerVM::drawStateDead(double rate) const
    {
        bool isRight = m_forward == Forward::Right;

        int32 frame = static_cast<int32>(s3d::Math::Lerp(0, 5, s3d::Pow(rate, 1.8)));
        if (frame == 5) {
            frame = 4;
        }
        auto pos = m_pos;
        if (frame == 4) {
            pos.y += 3;
        }
        m_texture(U"dead")({ isRight ? 80 : 0, frame * 80 }, {80, 80})
            .drawAt(pos, this->calcColor());
    }
    void PlayerVM::drawStateLadder() const
    {
        if (m_isAttacking) {
            this->drawStateLadderAtk();
            return;
        }
        m_texture(U"ladder")({ 40 * (static_cast<int32>(m_pos.y / 16) % 2), 0 }, { 40, 80 }).drawAt(m_pos, this->calcColor());
    }
    void PlayerVM::drawStateLadderAtk() const
    {
        auto page = static_cast<int32>(m_pos.y / 16) % 2;
        bool isRight = m_forward == Forward::Right;
        auto drawer = [this, page, isRight]() {
            

            m_texture(U"ladder_atk")({ isRight ? 70 : 0, 80 * page }, { 70, 80 }).drawAt(m_pos, this->calcColor());
        };
        double offsetX = 0.0;
        if (page == 0) {
            offsetX = isRight ? 17 : -27;
        } else {
            offsetX = isRight ? 18 : -26;
        }
        m_xto->setDrawFunc(drawer);
        m_oopartsView
            ->setCharacter(m_xto)
            .setTime(m_time)
            .setForward(m_forward)
            .setPos(m_pos + s3d::Vec2{ offsetX, -3 })
            .draw();
    }
    void PlayerVM::drawStateLadderTop() const
    {
        if (m_isAttacking) {
            this->drawStateLadderTopAtk();
            return;
        }
        m_texture(U"ladder")({ 80, 0 }, { 40, 80 }).drawAt(m_pos, this->calcColor());
    }
    void PlayerVM::drawStateLadderTopAtk() const
    {
        bool isRight = m_forward == Forward::Right;
        auto drawer = [this, isRight]() {

            m_texture(U"ladder_atk")({ isRight ? 70 : 0, 160 }, { 70, 80 }).drawAt(m_pos, this->calcColor());
        };
        double offsetX = isRight ? 17 : -22;
        m_xto->setDrawFunc(drawer);
        m_oopartsView
            ->setCharacter(m_xto)
            .setTime(m_time)
            .setForward(m_forward)
            .setPos(m_pos + s3d::Vec2{ offsetX, -3 })
            .draw();
    }
    void PlayerVM::drawStateDoor() const
    {
        m_texture(U"door")({ 40 * static_cast<int32>(Periodic::Sawtooth0_1(1s) * 2), 0 }, { 40, 80 }).drawAt(m_pos, this->calcColor());
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
