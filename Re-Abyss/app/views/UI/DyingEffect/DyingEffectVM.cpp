#include "DyingEffectVM.hpp"
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <abyss/commons/Constants.hpp>
#include <Siv3D.hpp>
namespace abyss::UI::DyingEffect
{
    DyingEffectVM::DyingEffectVM():
        m_texture(Resource::Assets::Main()->load(U"ui/DyingEffect/dying_effect.png"))
    {}

    void DyingEffectVM::draw() const
    {
        if (m_hp / m_maxHp > 1.0 / 6.0) {
            return;
        }
        ScopedRenderStates2D blend(BlendState::Additive);
        if (m_hp <= 0) {
            RectF(s3d::Vec2{0, 0}, Constants::AppResolutionF).draw(ColorF(1, 0, 0, 0.8));
            return;
        }
        auto color = ColorF(1, 0, 0, 0.8 - 0.4 * Periodic::Sawtooth0_1(1s, m_time));
        m_texture.draw(color);
    }

}
