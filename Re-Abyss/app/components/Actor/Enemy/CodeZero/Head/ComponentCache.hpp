#pragma once
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/ParentCtrl.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/Head/HeadCtrl.hpp>

namespace abyss::Actor::Enemy::CodeZero::Head
{
    class ComponentCache
    {
    protected:
        ParentCtrl* m_parent;
        HeadCtrl* m_head;
    public:
        void onCache(ActorObj* pActor)
        {
            m_parent = pActor->find<ParentCtrl>().get();
            m_head = pActor->find<HeadCtrl>().get();
        }
    };
}