#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/components/Effect/base/IDrawParts.hpp>
#include <Siv3D/Effect.hpp>

namespace abyss::Effect
{
    class SivEffect :
        public IComponent,
        public IDrawParts
    {
    public:
        SivEffect(std::unique_ptr<s3d::IEffect>&& effect);

        bool onDraw(double time) override;
    private:
        std::unique_ptr<s3d::IEffect> m_effect;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Effect::SivEffect>
    {
        using Base = Effect::IDrawParts;
    };
}