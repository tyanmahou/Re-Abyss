#include "OopartsVM.hpp"
#include <Siv3D.hpp>
#include <abyss/views/Actors/Common/KiraKiraEffect.hpp>
#include <abyss/controllers/System/System.hpp>

namespace abyss::Ooparts
{
    OopartsVM::OopartsVM():
        m_effectTimer(0.05, true, [this] {return Time::FromSec(this->m_time); })
    {
    }
    void OopartsVM::draw() const
    {
        const auto& pos = m_pos;
        double alpha = 0.4 * Periodic::Triangle0_1(0.1s, m_time);
        constexpr double period = 0.8;
        {
            auto* effects = m_pManager->getModule<Effects>();
            if (m_effectTimer.update()) {
                if (RandomBool(0.7)) {
                    effects->addWorldBack<KiraKiraEffect>(pos + RandomVec2({ -15, 15 }, { 0, 20 }));
                } else {
                    effects->addWorldBack<KiraKiraEffect>(pos + RandomVec2(17), KiraKiraEffect::Type2);
                }
            }
        }
        {
            ScopedRenderStates2D t2d(BlendState::Additive);

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
