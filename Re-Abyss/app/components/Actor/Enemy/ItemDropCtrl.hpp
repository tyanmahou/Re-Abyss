#pragma once
#include <abyss/components/base/Components.hpp>

namespace abyss::Actor::Enemy
{
    class ItemDropCtrl : 
        public IComponent
    {
    public:
        ItemDropCtrl(ActorObj* pActor);
    private:
        ActorObj* m_pActor;
    };
}