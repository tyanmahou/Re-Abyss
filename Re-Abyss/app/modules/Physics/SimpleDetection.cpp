#include "SimpleDetection.hpp"
#include <abyss/modules/Physics/base/IContacter.hpp>
#include <abyss/modules/Physics/base/ITerrain.hpp>
#include <abyss/utils/Collision/CollisionUtil.hpp>

namespace abyss::Physics
{
    void SimpleDetection::collisionAll(const s3d::Array<Ref<IContacter>>& contacters, const s3d::Array<Ref<ITerrain>>& terrains)
    {
        for (const auto& c : contacters) {
            if (!c || !c->isActive()) {
                continue;
            }

            for (const auto& t : terrains) {
                if (!t || !t->isActive()) {
                    continue;
                }
                if(c->id() == t->id())
                if (ColisionUtil::Intersects(c->getShape(), t->getData().region)) {
                    d->onCollision(t->getData());
                }
            }
        }
    }
}
