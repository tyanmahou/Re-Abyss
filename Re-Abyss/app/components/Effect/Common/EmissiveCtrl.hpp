#pragma once
#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/components/Effect/base/IDraw.hpp>
#include <abyss/components/Effect/base/Drawer.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Effect
{
	class EmissiveCtrl final :
		public IComponent,
		public IDraw
	{
	public:
		EmissiveCtrl(EffectObj* pObj);
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
    struct ComponentTree<Effect::EmissiveCtrl>
    {
        using Base = Effect::IDraw;
    };
}