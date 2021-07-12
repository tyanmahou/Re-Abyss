#include "OopartsView.hpp"
#include <Siv3D.hpp>
#include <abyss/views/Actor/Common/KiraKiraEffect.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>

namespace abyss::Actor::Ooparts
{
    OopartsView::OopartsView():
        m_effectTimer(0.05, true, [this] {return Clock::FromSec(this->getTime()); })
    {
    }
    void OopartsView::draw() const
    {
        const auto& pos = m_pos;
        double alpha = 0.4 * Periodic::Triangle0_1(0.1s, m_time);
        constexpr double period = 0.8;
        {
            if (m_drawCallback) {
                if (m_effectTimer.update()) {
                    if (RandomBool(0.7)) {
                        m_drawCallback->onAddEffect<KiraKiraEffect>(pos + RandomVec2({ -15, 15 }, { 0, 20 }));
                    } else {
                        m_drawCallback->onAddEffect<KiraKiraEffect>(pos + RandomVec2(17), KiraKiraEffect::Type2);
                    }
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

            if (m_character) {
                m_character
                    ->setPos(pos)
                    .setForward(m_forward)
                    .setTime(m_time)
                    .draw();
            }
        }
        {
            ScopedRenderStates2D t2d(BlendState::Additive);
            Circle(pos, Periodic::Triangle0_1(period / 2.0, m_time) * 5 + 10).draw(ColorF(1.0, alpha));
        }
    }

}
