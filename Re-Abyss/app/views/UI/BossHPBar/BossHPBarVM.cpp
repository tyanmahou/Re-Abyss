#include "BossHPBarVM.hpp"
#include <abyss/commons/Resource/Assets/Assets.hpp>
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
        m_texture(Resource::Assets::Main()->loadTexturePacker(U"ui/common/boss_hp_bar/boss_hp_bar.json")),
        m_pos(650, 495)
    {
    
    }

    void BossHPBarVM::draw() const
    {
        m_texture(U"base").draw(m_pos);
        double rate = s3d::Saturate(m_hp / m_maxHp);
        double offsetX = 216.0 * (1 - rate);
        m_texture(GetType(m_hp, m_maxHp)).uv(1 - rate, 0, rate, 1).draw(m_pos + s3d::Vec2{44 + offsetX, 15});
    }

}
