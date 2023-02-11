#pragma once

#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/modules/Actor/base/IUpdate.hpp>
#include <Siv3D/Vector2D.hpp>

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
            return m_offset;
        }

        bool isShakeing() const;
    private:
        ActorObj* m_pActor;

        double m_maxOffset = 0;
        double m_timeSec = 0.0;
        double m_elapsedSec = 0.0;

        double m_nextTargetTimeSec = 0.0;
        Vec2 m_offsetTarget;

        s3d::Vec2 m_offset;
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
