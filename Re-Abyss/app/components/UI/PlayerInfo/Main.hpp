#pragma once
#include <memory>
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/UI/base/IUpdate.hpp>
#include <abyss/components/UI/base/IDraw.hpp>
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
        Main(UIObj* pUi, Actor::IActor* actor);

        void onStart() override;

        void onUpdate() override;

        void onDraw() const override;
    private:
        UIObj* m_pUi;

        Actor::IActor* m_pActor;
        Ref<Actor::HP> m_hpModel;

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