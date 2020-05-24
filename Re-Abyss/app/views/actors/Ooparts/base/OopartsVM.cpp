#include "OopartsVM.hpp"
#include <Siv3D.hpp>
#include <abyss/views/Actors/Common/KiraKiraEffect.hpp>

namespace abyss::Ooparts
{
    OopartsVM::OopartsVM():
        m_effectTimer(0.05, true, [this] {return Time::FromSec(this->m_time); }),
        m_effect([this] {return Time::FromSec(this->m_time); })
    {
        m_effect.setSpeed(1.5);
    }
    void OopartsVM::draw() const
    {
        auto pos = m_pos + Vec2{
            15 * s3d::Sin(m_time * 2.0),
            10 * s3d::Sin(m_time * 4.0)
        };
        double alpha = 0.4 * Periodic::Triangle0_1(0.1s, m_time);
        constexpr double period = 0.8;
        {
            ScopedRenderStates2D t2d(BlendState::Additive);
            {
                if (m_effectTimer.update()) {
                    if (RandomBool(0.7)) {
                        m_effect.add<KiraKiraEffect>(pos + RandomVec2({ -15, 15 }, { 0, 20 }));
                    } else {
                        m_effect.add<KiraKiraEffect>(pos + RandomVec2(17), KiraKiraEffect::Type2);
                    }
                }
                m_effect.update();
            }
            Circle(pos, 17 * (1 - Periodic::Sawtooth0_1(period, m_time))).drawFrame(0, 1, ColorF(1.0, alpha));
            double s = 25 * Periodic::Triangle0_1(period / 2.0, m_time);
            RectF({ 0,0,s, s })
                .setCenter(pos)
                .rotated(Math::QuarterPi * Periodic::Square0_1(period, m_time))
                .drawFrame(0, 1, ColorF(1.0, 0.5 - alpha));
        }
        {
            auto charaColor = static_cast<s3d::int32>(m_time * 10.0) % 2 ? s3d::ColorF(1.0, 0.5) : s3d::ColorF(0.9);

            this->drawCharacter(pos, charaColor);
        }
        {
            ScopedRenderStates2D t2d(BlendState::Additive);
            Circle(pos, Periodic::Triangle0_1(period / 2.0, m_time) * 5 + 10).draw(ColorF(1.0, alpha));
        }
    }

}
