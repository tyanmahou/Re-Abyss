#pragma once
#include <memory>
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/UI/base/IUpdate.hpp>
#include <abyss/components/UI/base/IDraw.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::ui::PlayerInfo
{
    class Main : 
        public IComponent,
        public IUpdate,
        public IDraw
    {
        
    public:
        Main(IUserInterface* pUi, Actor::IActor* actor);

        void onStart() override;

        void onUpdate() override;

        void onDraw() const override;
    private:
        IUserInterface* m_pUi;

        Actor::IActor* m_pActor;
        Ref<Actor::HP> m_hpModel;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<ui::PlayerInfo::Main>
    {
        using Base = MultiComponents<ui::IUpdate, ui::IDraw>;
    };
}