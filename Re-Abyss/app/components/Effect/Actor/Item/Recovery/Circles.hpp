#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/components/Effect/base/IDrawParts.hpp>
#include <abyss/components/Effect/Actor/Item/Recovery/LocationCtrl.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Effect::Actor::Item::Recovery
{
    class Circles :
        public IComponent,
        public IDrawParts
    {
    public:
        Circles(EffectObj* pObj);
        ~Circles();

    public:
        void onStart() override;

        bool onDraw(double time) override;

    private:
        EffectObj* m_pObj;
        Ref<LocationCtrl> m_location;
        double m_startAngle = 0.0;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Effect::Actor::Item::Recovery::Circles>
    {
        using Base = MultiComponents<
            Effect::IDrawParts
        >;
    };
}