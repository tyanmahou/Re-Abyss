#pragma once
#include <memory>
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/modules/UI/base/IUpdate.hpp>
#include <abyss/modules/UI/base/IDraw.hpp>
#include <abyss/components/Actor/Common/DamageCtrl.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::UI::PlayerInfo
{
    class PlayerInfoExVM;

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
        Ref<Actor::HP> m_hp;
        Ref<Actor::DamageCtrl> m_damage;

        std::unique_ptr<PlayerInfoExVM> m_view;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<UI::PlayerInfo::Main>
    {
        using Base = MultiComponents<UI::IUpdate, UI::IDraw>;
    };
}