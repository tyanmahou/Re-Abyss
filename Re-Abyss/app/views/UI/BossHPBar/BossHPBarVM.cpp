#include <abyss/views/UI/BossHPBar/BossHPBarVM.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <abyss/params/UI/BossHPBar/Param.hpp>
#include <abyss/views/util/Anchor/AnchorUtil.hpp>
#include <Siv3D/Math.hpp>

namespace 
{
    s3d::String GetType(double hp, double maxHp)
    {
        if (hp > maxHp * 2.0 / 3.0) {
            return U"blue";
        }else if (hp > maxHp * 1.0 / 3.0) {
            return U"yellow";
        }else {
            return U"red";
        }
    }
}
namespace abyss::UI::BossHPBar
{
    BossHPBarVM::BossHPBarVM():
        m_texture(Resource::Assets::Main()->load(U"UI/BossHPBar/BossHpBar.json")),
        m_pos(AnchorUtil::FromBr(Param::BrPos))
    {
    
    }

    void BossHPBarVM::draw() const
    {
        m_texture(U"base").draw(m_pos);
        {
            double rate = s3d::Saturate(m_hpComboBuffer / m_maxHp);
            double offsetX = 216.0 * (1 - rate);
            RectF(m_pos + s3d::Vec2{ 44 + offsetX, 15 }, 216 * rate, 13).draw(ColorF(1, 0.95));
        }
        {
            double rate = s3d::Saturate(m_hp / m_maxHp);
            double offsetX = 216.0 * (1 - rate);
            m_texture(GetType(m_hp, m_maxHp)).uv(1 - rate, 0, rate, 1).draw(m_pos + s3d::Vec2{ 44 + offsetX, 15 });
        }
    }

}
