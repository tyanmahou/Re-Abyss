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

        void onDraw(double time) override;

        bool isEnd() const override
        {
            return m_isEnd;
        }
    private:
        bool m_isEnd = false;
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