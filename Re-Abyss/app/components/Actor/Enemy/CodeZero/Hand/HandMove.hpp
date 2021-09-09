#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Actor/base/IMove.hpp>
#include <abyss/components/Actor/base/IStateCallback.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/ParentCtrl.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/Hand/HandRecipe.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Actor::Enemy::CodeZero::Hand
{
    class HandMove :
        public IComponent,
        public IMove,
        public IStateCallback
    {
    public:
        HandMove(ActorObj* pActor);

        void setup(Executer executer) override;

        void onStart() override;

        void onMove() override;

        void onStateStart() override;

        void setParam(const HandRecipe& recipe)
        {
            m_param = recipe;
        }

        /// <summary>
        /// 向き更新
        /// </summary>
        void updateRotate() const;

        /// <summary>
        /// 追従開始
        /// </summary>
        void startForPursuit() const;

        /// <summary>
        /// 追従更新
        /// </summary>
        void updateForPursuit() const;

        /// <summary>
        /// 攻撃待機開始
        /// </summary>
        void startForAttackWait() const;

        /// <summary>
        /// 攻撃開始
        /// </summary>
        void startForAttack();

        /// <summary>
        /// 攻撃更新
        /// </summary>
        /// <returns>終わればfalse</returns>
        bool updateForAttack();

    private:
        ActorObj* m_pActor = nullptr;
        Ref<Body> m_body;
        Ref<RotateCtrl> m_rotate;
        Ref<ParentCtrl> m_parent;

        HandRecipe m_param;
        bool m_isReturn = false;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::Enemy::CodeZero::Hand::HandMove>
    {
        using Base = MultiComponents<
            Actor::IMove,
            Actor::IStateCallback
        >;
    };
}