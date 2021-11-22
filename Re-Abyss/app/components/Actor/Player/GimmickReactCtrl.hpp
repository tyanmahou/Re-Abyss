#pragma once

#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/components/Actor/base/IPostUpdate.hpp>

namespace abyss::Actor::Player
{
    class GimmickReactCtrl:
        public IComponent,
        public IPostUpdate
    {
    public:
        GimmickReactCtrl(ActorObj* pActor);

        void setup(Executer executer) override;
        void onPostUpdate() override;
    private:
        ActorObj* m_pActor;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::Player::GimmickReactCtrl>
    {
        using Base = MultiComponents<
            Actor::IPostUpdate
        >;
    };
}