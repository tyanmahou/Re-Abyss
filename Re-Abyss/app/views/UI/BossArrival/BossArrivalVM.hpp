#pragma once
#include <abyss/utils/TexturePacker/TexturePacker.hpp>

namespace abyss::UI::BossArrival
{
    class BossArrivalVM
    {
    public:
        BossArrivalVM();

        BossArrivalVM& setPos(const s3d::Vec2& pos);
        void draw() const;
    private:
        TexturePacker m_texture;
        s3d::Vec2 m_pos;
    };
}
