#include "MapCollisionModel.hpp"

#include <abyss/components/Actors/base/IPhysics.hpp>
#include <abyss/components/Actors/Commons/Terrain.hpp>

namespace abyss
{
    void SimpleMapCollision::collisionAll(const s3d::Array<Ref<Actor::IPhysics>>& physics, const s3d::Array<Ref<Actor::Terrain>>& terrains)
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
