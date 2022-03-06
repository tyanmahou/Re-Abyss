#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/components/Actor/base/IPostCollision.hpp>
#include <abyss/components/Actor/Common/HP.hpp>
#include <abyss/components/Actor/Common/ColCtrl.hpp>
#include <abyss/components/Actor/Common/IStateCallback.hpp>
#include <abyss/components/Actor/Common/IDamageCallback.hpp>
#include <abyss/components/Actor/Common/ComboHistory.hpp>
#include <abyss/utils/Ref/Ref.hpp>
#include <abyss/utils/TimeLite/Timer.hpp>

namespace abyss::Actor
{
    class DamageCtrl : 
        public IComponent,
        public IPostCollision,
        public IStateCallback
    {
    public:
        DamageCtrl(ActorObj* pActor);

        DamageCtrl& setInvincibleTime(double invincibleTimeSec);
        bool isInInvincibleTime() const;

        void setInInvincibleState(bool isInvincible)
        {
            m_isInvincibleState = isInvincible;
        }

        void onStart() override;
        void onPostCollision()override;

        void onStateStart() override
        {
            m_isActive = true;
            m_isInvincibleState = false;
        }
        void setActive(bool isActive)
        {
            m_isActive = isActive;
        }

        const s3d::Optional<DamageData>& getData() const
        {
            return m_damageData;
        }
    protected:
        Ref<HP> m_hp;
        Ref<ColCtrl> m_colCtrl;
        ActorObj* m_pActor;

        TimeLite::Timer m_invincibleTime;
        bool m_isInvincibleState = false;

        bool m_isActive = true;
        s3d::Optional<DamageData> m_damageData;

        ComboHistory m_comboHistory;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::DamageCtrl>
    {
        using Base = MultiComponents<
            Actor::IPostCollision,
            Actor::IStateCallback
        >;
    };
}