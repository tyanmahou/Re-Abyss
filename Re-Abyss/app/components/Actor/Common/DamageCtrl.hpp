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
        bool isInvincibleTime() const;

        void setInvincibleState(bool isInvincible, double invincibleTimeSec = 2);
        bool isInvincibleState() const
        {
            return m_isInvincibleState;
        }
        s3d::ColorF getInvincibleStateColor() const;

        void setActive(bool isActive)
        {
            m_isActive = isActive;
        }

        const s3d::Optional<DamageData>& getData() const
        {
            return m_damageData;
        }

        void onStart() override;
        void onPostCollision()override;

        void onStateStart() override;
    protected:
        Ref<HP> m_hp;
        Ref<ColCtrl> m_colCtrl;
        ActorObj* m_pActor;

        TimeLite::Timer m_invincibleTime;
        bool m_isInvincibleState = false;
        TimeLite::Timer m_invincibleStateColorTime;

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