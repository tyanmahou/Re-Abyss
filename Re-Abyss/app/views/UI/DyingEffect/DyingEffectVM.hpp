#pragma once
#include <Siv3D/Texture.hpp>

namespace abyss::UI::DyingEffect
{
    class DyingEffectVM
    {
    private:
        s3d::Texture m_texture;
        s3d::Vec2 m_pos;
        double m_hp = 1;
        double m_maxHp = 1;
        double m_time = 0;
    public:
        DyingEffectVM();

        DyingEffectVM& setHp(double hp)
        {
            m_hp = hp;
            return *this;
        }
        DyingEffectVM& setMaxHp(double maxHp)
        {
            m_maxHp = maxHp;
            return *this;
        }
        DyingEffectVM& setTime(double time)
        {
            m_time = time;
            return *this;
        }
        void draw() const;
    };
}