#include "SchieldVM.hpp"

#include <Siv3D.hpp>
#include <abyss/commons/ResourceManager/ResourceManager.hpp>
#include <abyss/commons/ColorDef.hpp>
#include <abyss/controllers/World/WorldTime.hpp>
#include <abyss/params/Actors/Enemy/Schield/Param.hpp>

namespace abyss::Schield
{
    SchieldVM::SchieldVM():
        m_texture(ResourceManager::Main()->loadTexturePacker(U"actors/Enemy/Schield/schield.json"))
    {}
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
    SchieldVM& SchieldVM::setIsDamaging(bool isDamaging)
    {
        m_isDamaging = isDamaging;
        return *this;
    }
    void SchieldVM::drawWait() const
    {
        auto&& tex = m_texture(U"wait");
        bool isRight = m_forward == Forward::Right;
        int32 page = static_cast<int32>(Periodic::Triangle0_1(Param::View::AnimeTimeSec, WorldTime::Time()) * 3.0);
        tex(0, 60*page, 150, 60).mirrored(isRight).drawAt(m_pos, ColorDef::OnDamage(m_isDamaging, WorldTime::Time()));
    }

    void SchieldVM::drawToWait(double t) const
    {
        int32 page = Min(static_cast<int32>(t * 8.0), 7);
        auto&& tex = m_texture(U"wait_to_attack3");
        bool isRight = m_forward == Forward::Right;
        tex(150 * (page / 4) , 60 * (page % 4), 150, 60)
            .mirrored(isRight)
            .drawAt(m_pos, ColorDef::OnDamage(m_isDamaging, WorldTime::Time()));
    }

    void SchieldVM::drawAttackPlus() const
    {
        return this->drawToAttackPlus(1.0);
    }

    void SchieldVM::drawToAttackPlus(double t) const
    {
        int32 page = Min(static_cast<int32>(t * 8.0), 7);
        auto&& tex = m_texture(U"wait_to_attack");
        bool isRight = m_forward == Forward::Right;
        tex(150 * (page / 4), 60 * (page % 4), 150, 60)
            .mirrored(isRight)
            .drawAt(m_pos, ColorDef::OnDamage(m_isDamaging, WorldTime::Time()));
    }

    void SchieldVM::drawAttackCross() const
    {
        return this->drawToAttackCross(1.0);
    }
    void SchieldVM::drawToAttackCross(double t) const
    {
        int32 page = Min(static_cast<int32>(t * 8.0), 7);
        auto&& tex = m_texture(U"wait_to_attack2");
        bool isRight = m_forward == Forward::Right;
        tex(120 * (page / 4), 60 * (page % 4), 120, 60)
            .mirrored(isRight)
            .drawAt(m_pos, ColorDef::OnDamage(m_isDamaging, WorldTime::Time()));
    }
}
