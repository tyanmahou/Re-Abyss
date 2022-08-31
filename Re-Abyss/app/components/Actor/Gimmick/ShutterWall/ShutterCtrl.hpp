#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/components/Actor/Common/TerrainProxy.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Actor::Gimmick::ShutterWall
{
    class ShutterCtrl :
        public IComponent
    {
    public:
        ShutterCtrl(ActorObj* pActor);

        void setup(Executer executer) override;
        void onStart()override;
    private:
        ActorObj* m_pActor;
        Ref<TerrainProxy> m_terrain;
    };
}
