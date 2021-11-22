#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/components/Effect/base/IDraw.hpp>
#include <abyss/views/Effect/Actor/Ooparts/Common/KiraKira/KiraKiraVM.hpp>

namespace abyss::Effect::Actor::Ooparts::KiraKira
{
    class Main :
        public IComponent,
        public IDraw
    {
    public:
        Main(EffectObj* pObj, const s3d::Vec2& pos, Type type);
        bool onDraw(double time) override;
    private:
        EffectObj* m_pObj;
        KiraKiraVM m_view;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Effect::Actor::Ooparts::KiraKira::Main>
    {
        using Base = MultiComponents<
            Effect::IDraw
        >;
    };
}