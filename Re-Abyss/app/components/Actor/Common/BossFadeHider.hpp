#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/modules/Actor/base/IPreDraw.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Actor
{
    class BossFadeMask;

    class BossFadeHider :
        public IComponent,
        public IPreDraw
    {
    public:
        BossFadeHider(ActorObj* pActor);
    public:
        void setup(Executer executer) override;

        void onStart() override;
    public:
        void onPreDraw() override;
    private:
        ActorObj* m_pActor;
        Ref<BossFadeMask> m_fadeMask;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::BossFadeHider>
    {
        using Base = MultiComponents<Actor::IPreDraw>;
    };
}
