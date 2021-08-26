#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Common/ITimeScale.hpp>
#include <abyss/components/Actor/base/IPostCollision.hpp>
#include <abyss/components/Actor/Commons/HP.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Actor::Gimmick::Bush
{
    class TimeScaleCtrl :
        public IComponent,
        public IPostCollision,
        public ITimeScale
    {
    public:
        TimeScaleCtrl(ActorObj* pActor);
        void onStart() override;
        void onPostCollision()override;

        double timeScale() override;
    private:
        ActorObj* m_pActor;
        Ref<CollisionCtrl> m_cols;
        bool m_isCollided = false;
        double m_scale = 0;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::Gimmick::Bush::TimeScaleCtrl>
    {
        using Base = MultiComponents<
            Actor::IPostCollision,
            ITimeScale
        >;
    };
}