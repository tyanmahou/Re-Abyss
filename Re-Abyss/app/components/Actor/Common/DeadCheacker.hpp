#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/Ref/Ref.hpp>
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/components/Actor/base/ILastUpdate.hpp>

namespace abyss::Actor
{
    class DeadChecker :
        public IComponent,
        public ILastUpdate
    {
    private:
        ActorObj* m_pActor = nullptr;
        Ref<HP> m_hp;

        bool m_isAutoDestroy = true;

        bool m_isDead = false;
        bool m_requestDead = false;
    public:
        DeadChecker(ActorObj* pActor);

        DeadChecker& setIsAutoDestroy(bool isAuto)
        {
            m_isAutoDestroy = isAuto;
            return *this;
        }

        /// <summary>
        /// 死亡リクエストをする
        /// </summary>
        void requestDead();

        bool isDead() const
        {
            return m_isDead;
        }
        void onStart()override;
        void onLastUpdate() override;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::DeadChecker>
    {
        using Base = Actor::ILastUpdate;
    };
}