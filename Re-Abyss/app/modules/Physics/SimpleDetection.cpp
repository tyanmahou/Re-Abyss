#include "SimpleDetection.hpp"
#include <abyss/modules/Physics/base/IDetector.hpp>
#include <abyss/modules/Physics/base/ITerrain.hpp>
#include <abyss/utils/Collision/CollisionUtil.hpp>

namespace abyss::Physics
{
    void SimpleDetection::collisionAll(const s3d::Array<Ref<IDetector>>& detectors, const s3d::Array<Ref<ITerrain>>& terrains)
    {
        for (const auto& d : detectors) {
            if (!d || !d->isActive()) {
                continue;
            }

            for (const auto& t : terrains) {
                if (!t || !t->isActive()) {
                    continue;
                }
                if(d->id() == t->id())
                if (ColisionUtil::Intersects(d->getShape(), t->getData().region)) {
                    d->onCollision(t->getData());
                }
            }
        }
    }
}
