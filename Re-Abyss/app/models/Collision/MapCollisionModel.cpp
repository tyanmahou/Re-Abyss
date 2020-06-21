#include "MapCollisionModel.hpp"

#include <abyss/models/Actors/base/IPhysicsModel.hpp>
#include <abyss/models/Actors/Commons/TerrainModel.hpp>

namespace abyss
{
    void SimpleMapCollision::collisionAll(const s3d::Array<Ref<IPhysicsModel>>& physics, const s3d::Array<Ref<TerrainModel>>& terrains)
    {
        for (const auto& p : physics) {
            if (!p || !p->isActive()) {
                continue;
            }

            for (const auto& t : terrains) {
                if (!t || p->getActor() == t->getActor()) {
                    continue;
                }

                if (p->intersects(t->getMapColInfo())) {
                    p->onCollision(t);
                }
            }
        }
    }
}
