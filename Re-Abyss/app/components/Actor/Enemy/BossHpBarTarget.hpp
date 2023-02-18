#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
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
    public:
        void onStart() override;
    private:
        ActorObj* m_pActor;
        Ref<HP> m_hp;
    };
}
