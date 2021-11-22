#pragma once

#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/components/Actor/base/IUpdate.hpp>
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
    private:
        ActorObj* m_pActor;
        double m_time = 0;
        double m_shakeTime = 0;
        double m_maxOffset = 5.0;
        s3d::Vec2 m_offset;
        double m_noiseOffset = 0.0;
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