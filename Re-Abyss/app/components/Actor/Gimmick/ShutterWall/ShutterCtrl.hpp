#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/modules/Actor/base/IPrePhysics.hpp>
#include <abyss/components/Actor/Common/ColCtrl.hpp>
#include <abyss/components/Actor/Common/TerrainProxy.hpp>
#include <abyss/utils/Ref/Ref.hpp>
#include <abyss/utils/TimeLite/Timer.hpp>
#include <abyss/utils/Coro/Fiber/FiberHolder.hpp>

namespace abyss::Actor::Gimmick::ShutterWall
{
    class ShutterCtrl :
        public IComponent,
        public IPrePhysics
    {
    public:
        ShutterCtrl(ActorObj* pActor);

        double getShutterRate() const;
        Coro::Fiber<> anim();
    public:
        void setup(Executer executer) override;
        void onStart()override;

        s3d::RectF getRegion() const;

    public:
        void onPrePhysics() override;
    private:
        ActorObj* m_pActor;
        Ref<TerrainProxy> m_terrain;
        Ref<ColCtrl> m_col;
        TimeLite::Timer m_shutterTimer;
        bool m_isWait = true;

        Coro::FiberHolder<> m_task;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::Gimmick::ShutterWall::ShutterCtrl>
    {
        using Base = MultiComponents<
            Actor::IPrePhysics
        >;
    };
}
