#pragma once
#include <abyss/components/base/Components.hpp>

namespace abyss::Actor::Enemy
{
    /// <summary>
    /// アイテムドロップ制御
    /// </summary>
    class ItemDropCtrl : 
        public IComponent
    {
    public:
        ItemDropCtrl(ActorObj* pActor);

        void drop() const;
    private:
        ActorObj* m_pActor;
    };
}