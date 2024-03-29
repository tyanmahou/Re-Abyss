#include <abyss/components/Actor/Item/ItemCollision.hpp>

#include <abyss/components/Actor/Item/IItemReactor.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/utils/Collision/CollisionUtil.hpp>

namespace abyss::Actor::Item
{
    ItemCollision::ItemCollision(ActorObj* pActor):
        m_pActor(pActor)
    {}

    void ItemCollision::setup(Executer executer)
    {
        executer.onStart().addAfter<IItemReactor>();
    }

    void ItemCollision::onStart()
    {
        m_collider = m_pActor->find<Collider>()->main();
        m_reactors = m_pActor->finds<IItemReactor>();
    }

    void ItemCollision::onGimmickReact(ActorObj* player)
    {
        auto playerCollider = player->find<Collider>()->main();
        if (!m_collider || !playerCollider) {
            return;
        }
        // 衝突してないならスルーする
        if (!ColisionUtil::Intersects(playerCollider->getCollider(), m_collider->getCollider())) {
            return;
        }

        for (auto&& reactor : m_reactors) {
            if (reactor) {
                reactor->onGained(player);
            }
        }
    }
}

