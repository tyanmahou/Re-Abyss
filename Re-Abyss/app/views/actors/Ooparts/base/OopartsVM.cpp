#include "OopartsVM.hpp"
#include <Siv3D.hpp>

#include <abyss/commons/ColorDef.hpp>
#include <abyss/controllers/World/WorldTime.hpp>

namespace abyss::Ooparts
{
    void OopartsVM::draw() const
    {
        auto time = WorldTime::Time();

        auto pos = m_pos + Vec2{
            15 * s3d::Sin(time * 2.0),
            10 * s3d::Sin(time * 4.0)
        };
        double alpha = 0.4 * Periodic::Triangle0_1(0.1s, time);
        constexpr double period = 0.8;
        {
            ScopedRenderStates2D t2d(BlendState::Additive);

            Circle(pos, 17 * (1 - Periodic::Sawtooth0_1(period, time))).drawFrame(0, 1, ColorF(1.0, alpha));
            double s = 25 * Periodic::Triangle0_1(period / 2.0, time);
            RectF({ 0,0,s, s })
                .setCenter(pos)
                .rotated(Math::QuarterPi * Periodic::Square0_1(period, time))
                .drawFrame(0, 1, ColorF(1.0, 0.5 - alpha));
        }
        {
            auto charaColor = static_cast<s3d::int32>(time * 10.0) % 2 ? s3d::ColorF(1.0, 0.5) : s3d::ColorF(0.9);

            this->drawCharacter(pos, charaColor, time);
        }
        {
            ScopedRenderStates2D t2d(BlendState::Additive);
            Circle(pos, Periodic::Triangle0_1(period / 2.0, time) * 5 + 10).draw(ColorF(1.0, alpha));
        }
    }

}
