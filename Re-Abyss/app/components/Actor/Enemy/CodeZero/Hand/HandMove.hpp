#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Actor/base/IMove.hpp>
#include <abyss/components/Actor/base/IStateCallback.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/ParentCtrl.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/Hand/HandDesc.hpp>
#include <abyss/utils/Ref/Ref.hpp>
#include <abyss/utils/Coro/TaskHolder/TaskHolder.hpp>

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

        void setParam(const HandDesc& recipe)
        {
            m_param = recipe;
        }

        /// <summary>
        /// 追従開始
        /// </summary>
        void startForPursuit(bool slowStart = false);

        /// <summary>
        /// 攻撃待機開始
        /// </summary>
        void startForAttackWait();

        /// <summary>
        /// 攻撃開始
        /// </summary>
        void startForAttack();

        /// <summary>
        /// チャージ開始
        /// </summary>
        void startForShotCharge();

        /// <summary>
        /// 移動終了
        /// </summary>
        /// <returns></returns>
        bool isMoveEnd() const;

        const Axis2& getAxis() const;
        const HandDesc& getDesc() const
        {
            return m_param;
        }
    private:
        Coro::Task<> movePursuit(bool slowStart = false);
        Coro::Task<> moveAttackWait();
        Coro::Task<> moveAttack();
        Coro::Task<> moveShotCharge();
    private:
        ActorObj* m_pActor = nullptr;
        Ref<Body> m_body;
        Ref<RotateCtrl> m_rotate;
        Ref<ParentCtrl> m_parent;

        HandDesc m_param;
        Coro::TaskHolder<> m_task;
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