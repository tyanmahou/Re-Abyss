#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/base/IComponent.hpp>
#include <abyss/modules/Physics/base/ITerrain.hpp>

namespace abyss::Actor
{
    class TerrainProxy :
        public IComponent
    {
        class Terrain;
    public:
        TerrainProxy(ActorObj* pActor);

        void setup(Executer executer) override;

        void onStart()override;
        void onEnd()override;

        TerrainProxy& setColDirection(ColDirection col);
        TerrainProxy& setRegion(const s3d::RectF& region);
        TerrainProxy& setExtData(std::shared_ptr<Physics::ITerrainExtData> data);

    private:
        ActorObj* m_pActor;
        std::shared_ptr<Terrain> m_terrain;
    };
}