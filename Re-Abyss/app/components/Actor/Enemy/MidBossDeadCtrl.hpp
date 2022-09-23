#pragma once
#include <abyss/modules/GameObject/Components.hpp>
#include <abyss/components/Actor/Common/IDeadCallback.hpp>
#include <abyss/modules/Temporary/TempFrag/TempKey.hpp>

namespace abyss::Actor::Enemy
{
    class MidBossDeadCtrl :
        public IComponent,
        public IDeadCallback
    {
    public:
        MidBossDeadCtrl(ActorObj* pActor, s3d::uint32 id);
    public:
        void onStart() override;
    public:
        void onDead() override;
    private:
        TempKey key() const;
    private:
        ActorObj* m_pActor;
        s3d::uint32 m_id;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::Enemy::MidBossDeadCtrl>
    {
        using Base = Actor::IDeadCallback;
    };
}