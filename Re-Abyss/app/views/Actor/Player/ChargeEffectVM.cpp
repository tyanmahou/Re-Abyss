#include <abyss/views/Actor/Player/ChargeEffectVM.hpp>
#include <abyss/params/Actor/Player/ShotParam.hpp>
#include <abyss/commons/ColorDef.hpp>

namespace
{
    using namespace abyss;

    ColorF ChargeToColor(double charge)
    {
        if (charge >= Actor::Player::ShotParam::Big::Charge) {
            return ColorDef::Shot::BigCharge;
        } else if (charge >= Actor::Player::ShotParam::Medium::Charge) {
            return ColorDef::Shot::MediumCharge;
        } else {
            return ColorF(1);
        }
    }
}

namespace abyss::Actor::Player
{
    void ChargeEffectVM::draw() const
    {
        if (m_charge <= ShotParam::Small::Charge) {
            return;
        }
        ScopedRenderStates2D t2d(BlendState::Additive);
        double a = 0.5 * Periodic::Triangle0_1(0.2s, m_time);

        ColorF color = ::ChargeToColor(m_charge);

        Circle(m_pos, 80 * (1 - Periodic::Sawtooth0_1(0.6s, m_time))).drawFrame(1, 1, color.setA(a));
        double s = 100 * Periodic::Triangle0_1(0.3s, m_time);
        RectF({ 0,0,s, s })
            .setCenter(m_pos)
            .rotated(Math::QuarterPi * Periodic::Square0_1(0.6s, m_time))
            .drawFrame(1, 1, color.setA(0.5 - a));

        if (m_charge >= ShotParam::Big::Charge) {
            Circle(m_pos, Periodic::Triangle0_1(0.3s, m_time) * 30 + 30).draw(color.setA(a));
        } else if (m_charge >= ShotParam::Medium::Charge) {
            Circle(m_pos, Periodic::Triangle0_1(0.3s, m_time) * 5 + 30).draw(color.setA(a));
        }
    }
}
