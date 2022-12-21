#pragma once
#include <abyss/modules/GameObject/Components.hpp>
#include <abyss/components/Actor/Common/DeployId.hpp>
#include <abyss/modules/Temporary/TempFrag/TempKey.hpp>

namespace abyss::Actor::Enemy
{
    class MidBossDeadCtrl :
        public IComponent
    {
    public:
        MidBossDeadCtrl(ActorObj* pActor);

        void notifyDead();

    public:
        void onStart() override;
    private:
        TempKey key() const;
    private:
        ActorObj* m_pActor;
        Ref<DeployId> m_deployId;
    };
}
