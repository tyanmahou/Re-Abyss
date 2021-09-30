#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Actor/base/IPostCollision.hpp>
#include <abyss/components/Actor/Common/HP.hpp>
#include <abyss/components/Actor/Common/CollisionCtrl.hpp>
#include <abyss/utils/Ref/Ref.hpp>
#include <abyss/utils/TimeLite/Timer.hpp>

namespace abyss::Actor::Enemy::CodeZero
{
    class ParentCtrl;
}
namespace abyss::Actor::Enemy::CodeZero::Head
{
    class DamageCtrl :
        public IComponent,
        public IPostCollision
    {
    protected:
        Ref<CollisionCtrl> m_col;
        Ref<ParentCtrl> m_parent;
        ActorObj* m_pActor;

        TimeLite::Timer m_invincibleTime;
    public:
        DamageCtrl(ActorObj* pActor);

        DamageCtrl& setInvincibleTime(double invincibleTimeSec);
        bool isInInvincibleTime() const;

        void onStart() override;
        void onPostCollision()override;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::Enemy::CodeZero::Head::DamageCtrl>
    {
        using Base = Actor::IPostCollision;
    };
}