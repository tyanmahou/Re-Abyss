#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Effect/base/IDraw.hpp>
#include <Siv3D/Effect.hpp>

namespace abyss::Effect
{
    class SivEffect :
        public IComponent,
        public IDraw
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
        using Base = Effect::IDraw;
    };
}