#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/components/Actor/Common/HP.hpp>
#include <abyss/components/Actor/Common/DamageCtrl.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Actor::Enemy
{
    /// <summary>
    /// BossHpBarのターゲット
    /// 検索用
    /// </summary>
    class BossHpBarTarget : public IComponent
    {
    public:
        BossHpBarTarget(ActorObj* pActor);

        const Ref<HP>& hp() const
        {
            return m_hp;
        }
        const Ref<DamageCtrl>& damageCtrl() const
        {
            return m_damageCtrl;
        }
        ActorObj* actor() const
        {
            return m_pActor;
        }
    public:
        void onStart() override;
    private:
        ActorObj* m_pActor;
        Ref<HP> m_hp;
        Ref<DamageCtrl> m_damageCtrl;
    };
}
