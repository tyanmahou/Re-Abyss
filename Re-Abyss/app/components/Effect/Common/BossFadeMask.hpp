#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/components/Effect/base/IDraw.hpp>
#include <abyss/components/Effect/base/Drawer.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Effect
{
	class BossFadeMask final :
        public IComponent,
        public IDraw
	{
    public:
        BossFadeMask(EffectObj* pObj);
    public:
        void onStart() override;

        DrawLayer getLayer() const override;
        double getOrder() const override;

        void onDraw() const override;
    private:
        EffectObj* m_pObj;
        Ref<Drawer> m_drawer;
	};
}

namespace abyss
{
    template<>
    struct ComponentTree<Effect::BossFadeMask>
    {
        using Base = Effect::IDraw;
    };
}