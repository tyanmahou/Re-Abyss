#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/components/Effect/base/IDraw.hpp>
#include <abyss/components/Actor/Common/ILocator.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Effect::Actor::Item::Recovery
{
    class Main :
        public IComponent,
        public IDraw
    {
    public:
        Main(EffectObj* pObj, const Ref<abyss::Actor::ILocator>& locator);
        ~Main();

    public:
        bool onDraw(double time) override;

    private:
        EffectObj* m_pObj;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Effect::Actor::Item::Recovery::Main>
    {
        using Base = MultiComponents<
            Effect::IDraw
        >;
    };
}