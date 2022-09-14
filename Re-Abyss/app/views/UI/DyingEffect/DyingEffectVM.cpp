#include <abyss/views/UI/DyingEffect/DyingEffectVM.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <abyss/commons/Constants.hpp>
#include <Siv3D.hpp>

namespace abyss::UI::DyingEffect
{
    DyingEffectVM::DyingEffectVM():
        m_texture(Resource::Assets::Main()->load(U"UI/DyingEffect/DyingEffect.png"))
    {}

    void DyingEffectVM::draw() const
    {
        if (m_hp > 1.0) {
            return;
        }
        if (m_hp <= 0) {
            return;
        }
        ScopedRenderStates2D blend(BlendState::Additive);
        auto color = ColorF(1, 0, 0, 0.8 - 0.4 * Periodic::Sawtooth0_1(1s, m_time));
        m_texture.draw(color);
    }

}
