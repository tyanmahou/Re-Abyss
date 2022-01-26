#include <abyss/modules/Physics/SimpleDetection.hpp>

#include <abyss/modules/Physics/base/IContacter.hpp>
#include <abyss/modules/Physics/base/ITerrain.hpp>
#include <abyss/utils/Collision/CollisionUtil.hpp>

namespace abyss::Physics
{
    void SimpleDetection::collisionAll(const s3d::Array<std::shared_ptr<IContacter>>& contacters, const s3d::Array<std::shared_ptr<ITerrain>>& terrains)
    {
        for (const auto& c : contacters) {
            if (!c || !c->isActive()) {
                continue;
            }

            for (const auto& t : terrains) {
                if (!t || !t->isActive()) {
                    continue;
                }
                if (c->id() == t->id()) {
                    // 同じidならスルー
                    continue;
                }
                if (ColisionUtil::Intersects(c->getShape(), t->getData().region)) {
                    c->onCollision(t->getData());
                }
            }
        }
    }
}
