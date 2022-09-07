#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/components/Actor/base/IPrePhysics.hpp>
#include <abyss/components/Actor/Common/TerrainProxy.hpp>
#include <abyss/utils/Ref/Ref.hpp>
#include <abyss/utils/TimeLite/Timer.hpp>
#include <abyss/utils/Coro/Task/TaskHolder.hpp>

namespace abyss::Actor::Gimmick::ShutterWall
{
    class ShutterCtrl :
        public IComponent,
        public IPrePhysics
    {
    public:
        ShutterCtrl(ActorObj* pActor);

        double getShutterRate() const;
        Coro::Task<> anim();
    public:
        void setup(Executer executer) override;
        void onStart()override;
    public:
        void onPrePhysics() override;
    private:
        ActorObj* m_pActor;
        Ref<TerrainProxy> m_terrain;
        TimeLite::Timer m_shutterTimer;
        bool m_isWait = true;

        Coro::TaskHolder<> m_task;
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
