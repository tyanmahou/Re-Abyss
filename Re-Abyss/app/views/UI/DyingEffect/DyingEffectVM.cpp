#include "DyingEffectVM.hpp"
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <abyss/commons/Constants.hpp>
#include <Siv3D.hpp>
namespace abyss::ui::DyingEffect
{
    DyingEffectVM::DyingEffectVM():
        m_texture(Resource::Assets::Main()->loadTexture(U"ui/common/dying_effect/dying_effect.png"))
    {}

    void DyingEffectVM::draw() const
    {
        if (m_hp / m_maxHp > 1.0 / 6.0) {
            return;
        }
        ScopedRenderStates2D blend(BlendState::Additive);
        if (m_hp <= 0) {
            Constants::GameScreen.draw(ColorF(1, 0, 0, 0.8));
            return;
        }
        auto color = ColorF(1, 0.8 - 0.4 * Periodic::Sawtooth0_1(1s, m_time));
        m_texture.draw(Constants::GameScreenOffset, color);
    }

}
