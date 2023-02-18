#include <abyss/views/Actor/Enemy/Schield/SchieldVM.hpp>

#include <Siv3D.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <abyss/params/Actor/Enemy/Schield/Param.hpp>

namespace abyss::Actor::Enemy::Schield
{
    SchieldVM::SchieldVM():
        m_texture(Resource::Assets::Main()->load(U"Actor/Enemy/Schield/Schield.json")),
        m_textureOver(Resource::Assets::Main()->load(U"Actor/Enemy/Schield/SchieldOver.json"))
    {}
    SchieldVM& SchieldVM::setTime(double time)
    {
        m_time = time;
        return *this;
    }
    SchieldVM& SchieldVM::setPos(const s3d::Vec2& pos)
    {
        m_pos = s3d::Round(pos);
        return *this;
    }
    SchieldVM& SchieldVM::setForward(const Forward& forward)
    {
        m_forward = forward;
        return *this;
    }
    SchieldVM& SchieldVM::setColorMul(const s3d::ColorF color)
    {
        m_colorMul = color;
        return *this;
    }

    void SchieldVM::draw() const
    {
        switch (m_motion) {
        case Motion::Wait:
            return this->drawWait();
        case Motion::ToWait:
            return this->drawToWait(m_animeTime);
        case Motion::AttackPlus:
            return this->drawAttackPlus();
        case Motion::ToAttackPlus:
            return this->drawToAttackPlus(m_animeTime);
        case Motion::AttackCross:
            return this->drawAttackCross();
        case Motion::ToAttackCross:
            return this->drawToAttackCross(m_animeTime);
        default:
            break;
        }
    }

    void SchieldVM::drawWait() const
    {
        bool isRight = m_forward.isRight();
        int32 page = static_cast<int32>(Periodic::Triangle0_1(Param::View::AnimeTimeSec, m_time) * 3.0);
        {
            auto&& tex = m_texture(U"wait");
            tex(0, 60 * page, 150, 60).mirrored(isRight).drawAt(m_pos, m_colorMul);
        }
        {
            auto&& tex = m_textureOver(U"wait_over");
            tex(0, 60 * page, 150, 60).mirrored(isRight).drawAt(m_pos);
        }
    }

    void SchieldVM::drawToWait(double t) const
    {
        int32 page = Min(static_cast<int32>(t * 8.0), 7);
        bool isRight = m_forward.isRight();
        {
            auto&& tex = m_texture(U"wait_to_attack3");
            tex(150 * (page / 4), 60 * (page % 4), 150, 60)
                .mirrored(isRight)
                .drawAt(m_pos, m_colorMul);
        }
        {
            auto&& tex = m_textureOver(U"wait_to_attack3_over");
            tex(150 * (page / 4), 60 * (page % 4), 150, 60)
                .mirrored(isRight)
                .drawAt(m_pos);
        }
    }

    void SchieldVM::drawAttackPlus() const
    {
        return this->drawToAttackPlus(1.0);
    }

    void SchieldVM::drawToAttackPlus(double t) const
    {
        int32 page = Min(static_cast<int32>(t * 8.0), 7);
        bool isRight = m_forward.isRight();
        {
            auto&& tex = m_texture(U"wait_to_attack");
            tex(150 * (page / 4), 60 * (page % 4), 150, 60)
                .mirrored(isRight)
                .drawAt(m_pos, m_colorMul);
        }
        {
            auto&& tex = m_textureOver(U"wait_to_attack_over");
            tex(150 * (page / 4), 60 * (page % 4), 150, 60)
                .mirrored(isRight)
                .drawAt(m_pos);
        }
    }

    void SchieldVM::drawAttackCross() const
    {
        return this->drawToAttackCross(1.0);
    }
    void SchieldVM::drawToAttackCross(double t) const
    {
        int32 page = Min(static_cast<int32>(t * 8.0), 7);
        auto&& tex = m_texture(U"wait_to_attack2");
        bool isRight = m_forward.isRight();
        tex(120 * (page / 4), 60 * (page % 4), 120, 60)
            .mirrored(isRight)
            .drawAt(m_pos, m_colorMul);
    }
}
