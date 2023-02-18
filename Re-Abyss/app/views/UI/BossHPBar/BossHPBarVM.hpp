#pragma once
#include <abyss/utils/TexturePacker/TexturePacker.hpp>

namespace abyss::UI::BossHPBar
{
    class BossHPBarVM
    {
    public:
        BossHPBarVM();

        BossHPBarVM& setHp(double hp)
        {
            m_hp = hp;
            return *this;
        }
        BossHPBarVM& setHpComboBuffer(double hpComboBuffer)
        {
            m_hpComboBuffer = hpComboBuffer;
            return *this;
        }
        BossHPBarVM& setMaxHp(double maxHp)
        {
            m_maxHp = maxHp;
            return *this;
        }
        void draw() const;

    private:
        TexturePacker m_texture;
        s3d::Vec2 m_pos;
        double m_hp = 1;
        double m_hpComboBuffer = 1;
        double m_maxHp = 1;
    };
}
