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

    public:
        void setup(Executer executer) override;
        void onStart()override;
    public:
        void onPrePhysics() override;
    private:
        ActorObj* m_pActor;
        Ref<TerrainProxy> m_terrain;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::MapCollider>
    {
        using Base = MultiComponents<
            Actor::IPrePhysics
        >;
    };
}
