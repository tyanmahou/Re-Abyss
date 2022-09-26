#pragma once
#include <abyss/modules/GameObject/Components.hpp>
#include <abyss/modules/Temporary/TempFrag/TempKey.hpp>

namespace abyss::Actor::Enemy
{
    class MidBossDeadCtrl :
        public IComponent
    {
    public:
        MidBossDeadCtrl(ActorObj* pActor, s3d::uint32 id);

        void notifyDead();

    public:
        void onStart() override;
    private:
        TempKey key() const;
    private:
        ActorObj* m_pActor;
        s3d::uint32 m_id;
    };
}
