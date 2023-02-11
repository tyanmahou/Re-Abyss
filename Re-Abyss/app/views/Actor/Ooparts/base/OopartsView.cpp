#include <abyss/views/Actor/Ooparts/base/OopartsView.hpp>
#include <Siv3D.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>

namespace abyss::Actor::Ooparts
{
    OopartsView::OopartsView()
    {
    }
    void OopartsView::draw() const
    {
        double alpha = 0.4 * Periodic::Triangle0_1(0.1s, m_time);
        constexpr double period = 0.8;

        if (m_pipeline & Pipeline::Back) {
            ScopedRenderStates2D t2d(BlendState::Additive);

            Circle(m_pos, 17 * (1 - Periodic::Sawtooth0_1(period, m_time))).drawFrame(0, 1, ColorF(1.0, alpha));
            double s = 25 * Periodic::Triangle0_1(period / 2.0, m_time);
            RectF({ 0,0,s, s })
                .setCenter(m_pos)
                .rotated(Math::QuarterPi * Periodic::Square0_1(period, m_time))
                .drawFrame(0, 1, ColorF(1.0, 0.5 - alpha));
        }
        if (m_pipeline & Pipeline::Character) {
            auto charaColor = static_cast<s3d::int32>(m_time * 10.0) % 2 ? s3d::ColorF(1.0, 0.5) : s3d::ColorF(0.9);

            if (m_character) {
                m_character
                    ->setPos(m_pos)
                    .setForward(m_forward)
                    .setTime(m_time)
                    .draw();
            }
        }
        if (m_pipeline & Pipeline::Front) {
            ScopedRenderStates2D t2d(BlendState::Additive);
            Circle(m_pos, Periodic::Triangle0_1(period / 2.0, m_time) * 5 + 10).draw(ColorF(1.0, alpha));
        }
    }

}
