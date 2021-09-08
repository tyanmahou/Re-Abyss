#pragma once
#include <abyss/modules/Actor/base/ActorObj.hpp>

#include <abyss/components/Actor/Commons/HP.hpp>
#include <abyss/components/Actor/Commons/Body.hpp>
#include <abyss/components/Actor/Commons/ScaleCtrl.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/ParentCtrl.hpp>

namespace abyss::Actor::Enemy::CodeZero::Shot
{
    class ComponentCache
    {
    protected:
        ParentCtrl* m_parent;
        Body* m_body;
        ScaleCtrl* m_scale;
    public:
        void onCache(ActorObj* pActor)
        {
            m_parent = pActor->find<ParentCtrl>().get();
            m_body = pActor->find<Body>().get();
            m_scale = pActor->find<ScaleCtrl>().get();
        }
    };
}