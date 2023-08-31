#pragma once
#include <abyss/utils/TexturePacker/TexturePacker.hpp>

namespace abyss::UI::BossArrival
{
    class BossArrivalVM
    {
    public:
        BossArrivalVM();

        BossArrivalVM& setPos(const s3d::Vec2& pos);

        BossArrivalVM& setTimeRate(double timeRate)
        {
            m_timeRate = timeRate;
            return *this;
        }
        void draw() const;
    private:
        TexturePacker m_texture;
        s3d::Vec2 m_pos;
        double m_timeRate = 0;
    };
}
