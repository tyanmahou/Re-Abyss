#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/components/Actor/base/IPrePhysics.hpp>
#include <abyss/components/Actor/Common/TerrainProxy.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Actor::Gimmick::ShutterWall
{
    class ShutterCtrl :
        public IComponent,
        public IPrePhysics
    {
    public:
        ShutterCtrl(ActorObj* pActor);

        double getShutterRate() const
        {
            return m_shutterRate;
        }
    public:
        void setup(Executer executer) override;
        void onStart()override;
    public:
        void onPrePhysics() override;
    private:
        ActorObj* m_pActor;
        Ref<TerrainProxy> m_terrain;
        double m_shutterRate = 0.0;
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
