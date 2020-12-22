#pragma once
#include <memory>
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/UI/base/IUpdate.hpp>
#include <abyss/components/UI/base/IDraw.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::ui::DyingEffect
{
    class DyingEffectVM;
}
namespace abyss::ui::DyingEffect
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
        Ref <Actor::HP> m_hpModel;
        std::unique_ptr<DyingEffectVM> m_view;

        double m_hp = 0;
        double m_maxHp = 1;

    };
}

namespace abyss
{
    template<>
    struct ComponentTree<ui::DyingEffect::Main>
    {
        using Base = MultiComponents<ui::IUpdate, ui::IDraw>;
    };
}