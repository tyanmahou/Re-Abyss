#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/Ref/Ref.hpp>
#include <abyss/components/base/IComponent.hpp>
#include <abyss/models/Actors/base/ILastUpdateModel.hpp>

namespace abyss::Actor
{
    class DeadChecker :
        public IComponent,
        public ILastUpdateModel
    {
    private:
        IActor* m_pActor = nullptr;
        Ref<HP> m_hp;

        bool m_isAutoDestroy = true;

        bool m_isDead = false;
        bool m_requestDead = false;
    public:
        DeadChecker(IActor* pActor);

        DeadChecker& setIsAutoDestroy(bool isAuto)
        {
            m_isAutoDestroy = isAuto;
            return *this;
        }

        /// <summary>
        /// 死亡リクエストをする
        /// </summary>
        void requestDead();

        void setup() override;
        void onLastUpdate() override;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::DeadChecker>
    {
        using Base = ILastUpdateModel;
    };
}