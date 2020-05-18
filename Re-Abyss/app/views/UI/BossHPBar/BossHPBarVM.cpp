#include "BossHPBarVM.hpp"
#include <abyss/commons/ResourceManager/ResourceManager.hpp>
#include <Siv3D/Math.hpp>

namespace 
{
    s3d::String GetType(double hp, double maxHp)
    {
        if (hp >= maxHp * 2.0 / 3.0) {
            return U"blue";
        }else if (hp >= maxHp * 1.0 / 3.0) {
            return U"yellow";
        }else {
            return U"red";
        }
    }
}
namespace abyss::ui
{
    BossHPBarVM::BossHPBarVM():
        m_texture(ResourceManager::Main()->loadTexturePacker(U"ui/common/boss_hp_bar/boss_hp_bar.json")),
        m_pos(650, 495)
    {
    
    }

    void BossHPBarVM::draw() const
    {
        m_texture(U"base").draw(m_pos);
        double rate = s3d::Saturate(m_hp / m_maxHp);
        double offsetX = 216.0 * (1 - rate);
        m_texture(GetType(m_hp, m_maxHp)).uv(1 - rate, 0, rate, 1).draw(m_pos + s3d::Vec2{44 + offsetX, 15});
        m_texture(U"text_boss").draw(m_pos);

        {
            s3d::Vec2 pos{ 100,200 };
            m_texture(U"base")(10, 0, 307, 46).resized({ 200, 46 }).rotated(s3d::ToRadians(90)).drawAt(pos);
            m_texture(U"text_boss")(10, 0, 307, 46).resized({ 200, 46 }).rotated(s3d::ToRadians(90)).drawAt(pos);
        }
        {
            s3d::Vec2 pos{ 300,200 };
            static int rad = 0;
            static s3d::Texture tex(U"work/UI/common/hpbar/base.png");
            tex(10, 0, 307, 46).rotated(s3d::ToRadians(++rad / 20)).draw(pos);
            m_texture(U"base")(10, 0, 307, 46).rotated(s3d::ToRadians(++rad / 20)).draw(pos);
            m_texture(U"text_boss")(10, 0, 307, 46).rotated(s3d::ToRadians(++rad / 20)).draw(pos);
        }
        {
            static TexturePacker old(U"resources/images/ui/common/boss_hp_bar/old/boss_hp_bar.json");
            s3d::Vec2 pos{ 200,200 };
            old(U"base")(10, 0, 307, 46).resized({ 200, 46 }).rotated(s3d::ToRadians(90)).drawAt(pos);
            old(U"text_boss")(10, 0, 307, 46).resized({ 200, 46 }).rotated(s3d::ToRadians(90)).drawAt(pos);
        }
    }

}
