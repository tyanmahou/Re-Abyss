#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/modules/Actor/base/IPreDraw.hpp>
#include <abyss/utils/Ref/Ref.hpp>
#include <abyss/components/Actor/Ooparts/KiraKiraAlgorithm.hpp>
#include <abyss/commons/Fwd.hpp>

namespace abyss::Actor::Ooparts
{
    class KiraKiraCtrl :
        public IComponent,
        public IPreDraw
    {
    public:
        KiraKiraCtrl(ActorObj* pActor);

        void setup(Executer executer) override;
        void onStart() override;
        void onPreDraw() override;
    private:
        ActorObj* m_pActor = nullptr;
        Ref<Body> m_body;

        KiraKiraAlgorithm m_algo;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::Ooparts::KiraKiraCtrl>
    {
        using Base = Actor::IPreDraw;
    };
}