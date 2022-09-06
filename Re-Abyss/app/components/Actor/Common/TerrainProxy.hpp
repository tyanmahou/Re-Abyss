#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/GameObject/IComponent.hpp>
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
        TerrainProxy& setTag(const Physics::TagType& tag);
        TerrainProxy& setExtData(std::shared_ptr<Physics::ITerrainExtData> data);
        TerrainProxy& setActive(bool isActive);

        const s3d::Vec2& tl() const;
    private:
        ActorObj* m_pActor;
        std::shared_ptr<Terrain> m_terrain;
    };
}
