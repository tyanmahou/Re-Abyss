#include "KingDuxVM.hpp"
#include <abyss/commons/ColorDef.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <abyss/params/Actor/Enemy/KingDux/Param.hpp>
#include <Siv3D.hpp>

namespace abyss::Actor::Enemy::KingDux
{
    KingDuxVM::KingDuxVM() :
        m_texture(Resource::Assets::Main()->load(U"actors/Enemy/KingDux/king_dux.json"))
    {}
    KingDuxVM& KingDuxVM::setTime(double time)
    {
        m_time = time;
        return *this;
    }
    KingDuxVM& KingDuxVM::setPos(const s3d::Vec2& pos)
    {
        m_pos = s3d::Round(pos);
        return *this;
    }
    KingDuxVM& KingDuxVM::setEyePos(const s3d::Vec2& posL, const s3d::Vec2& posR)
    {
        m_eyePosL = posL;
        m_eyePosR = posR;
        return *this;
    }
    KingDuxVM& KingDuxVM::setIsDamaging(bool isDamaging)
    {
        m_isDamaging = isDamaging;
        return *this;
    }
    void KingDuxVM::draw() const
    {
        auto color = ColorDef::OnDamage(m_isDamaging, m_time);

        // 右目
        {
            auto posBase = m_pos + Param::Base::EyeR;
            Circle(posBase, 70).draw();
            Circle(posBase + m_eyePosR, 24).draw(Palette::Black);
        }
        // 左目
        {
            auto posBase = m_pos + Param::Base::EyeL;
            Circle(posBase, 70).draw();
            double r = 24;
            if (m_isDamaging) {
                double rate = s3d::Periodic::Triangle0_1(0.3, m_time);
                r = s3d::Math::Lerp(r, 30, rate);
            }
            Circle(posBase + m_eyePosL, r).draw(Palette::Black);
        }
        // 体
        {
            m_texture(U"base").drawAt(m_pos, color);
        }
        // 口
        {
            auto rate = s3d::Periodic::Sine0_1(3.0, m_time);
            auto offsetX = 0.15 * (1 - rate);
            auto offsetY = s3d::Math::Lerp(-0.3, 0.2, rate);

            m_texture(U"mouth").scaled(1.0 + offsetX, 1.0 + offsetY).drawAt(m_pos + Param::Base::MouthPos, color);
        }
    }
}
