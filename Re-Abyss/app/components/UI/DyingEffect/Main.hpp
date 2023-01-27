#pragma once
#include <memory>
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/modules/UI/base/IUpdate.hpp>
#include <abyss/modules/UI/base/IDraw.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::UI::DyingEffect
{
    class DyingEffectVM;
}
namespace abyss::UI::DyingEffect
{
    class Main : 
        public IComponent,
        public IUpdate,
        public IDraw
    {
        
    public:
        Main(UIObj* pUi, Actor::ActorObj* actor);
        ~Main();
        void onStart() override;

        void onUpdate() override;

        void onDraw() const override;
    private:
        UIObj* m_pUi;

        Actor::ActorObj* m_pActor;
        Ref <Actor::HP> m_hpModel;
        std::unique_ptr<DyingEffectVM> m_view;

        double m_hp = 0;
        double m_maxHp = 1;

    };
}

namespace abyss
{
    template<>
    struct ComponentTree<UI::DyingEffect::Main>
    {
        using Base = MultiComponents<UI::IUpdate, UI::IDraw>;
    };
}