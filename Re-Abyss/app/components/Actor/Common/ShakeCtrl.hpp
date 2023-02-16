#pragma once

#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/modules/Actor/base/IUpdate.hpp>
#include <abyss/utils/Shake/SimpleShake.hpp>

namespace abyss::Actor
{
    /// <summary>
    /// 揺れ制御
    /// </summary>
    class ShakeCtrl :
        public IComponent,
        public IUpdate
    {
    public:
        ShakeCtrl(ActorObj* pActor);

        void onUpdate();

        /// <summary>
        /// リクエスト
        /// </summary>
        /// <param name="maxOffset">最大オフセット</param>
        /// <param name="timeSec">揺れ時間</param>
        void request(double maxOffset = 3.0, double timeSec = 0.3);

        const s3d::Vec2& getShakeOffset() const
        {
            return m_shake.getShakeOffset();
        }

        bool isShakeing() const;
    private:
        ActorObj* m_pActor;

        Shake::SimpleShake m_shake;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::ShakeCtrl>
    {
        using Base = abyss::MultiComponents<
            Actor::IUpdate
        >;
    };
}
