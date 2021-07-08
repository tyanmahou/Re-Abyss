#include "MapCollider.hpp"
#include <abyss/modules/Actor/base/ActorObj.hpp>

#include <abyss/components/Actor/base/ICollider.hpp>
#include <abyss/components/Actor/Commons/Body.hpp>
#include <abyss/components/Actor/Commons/Foot.hpp>
#include <abyss/components/Actor/Map/Ladder/LadderProxy.hpp>
#include <abyss/components/Actor/Map/PenetrateFloor/PenetrateFloorProxy.hpp>

#include <abyss/modules/Camera/Camera.hpp>
#include <abyss/utils/Collision/SweepUtil.hpp>
#include <abyss/types/CShape.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>

namespace abyss::Actor
{
    class MapCollider::Result
    {
    private:
        //s3d::Array<Ref<Terrain>> m_results;
        ColDirection m_col;
    public:
        Result() = default;

        void add(ColDirection col)
        {
            m_col |= col;
        }

        //void add(const Ref<Terrain>& terrain)
        //{
        //    m_results.push_back(terrain);
        //}
        void onReflesh()
        {
            //m_results.clear();
            m_col = ColDirection::None;
        }
        bool isHitGround() const
        {
            return m_col.isUp();
        }

        bool isHitWall() const
        {
            return m_col.isLeft() || m_col.isRight();
        }

        bool isHitWall(Forward forward) const
        {
            if (forward == Forward::Left && m_col.isRight()) {
                return true;
            }
            if (forward == Forward::Right && m_col.isLeft()) {
                return true;
            }
            return false;
        }

        bool isHitAny() const
        {
            return false;// !m_results.empty();
        }
    };

    MapCollider::MapCollider(ActorObj* pActor, bool useBody):
        m_pActor(pActor),
        m_result(std::make_unique<Result>()),
        m_useBody(useBody)
    {}
    void MapCollider::onStart()
    {
        m_body = m_pActor->find<Body>();
        m_collider = m_pActor->find<ICollider>();
        m_foot = m_pActor->find<Foot>();
    }

    CShape MapCollider::calcCollider() const
    {
        if (m_useBody) {
            // Body使用
            if (!m_isEnableMoveHistory) {
                return m_body->region();
            } else {
                // 移動差分をみて、6角形で考える
                return SweepUtil::Sweep(m_body->region(), -m_body->moveDiff());
            }
        }
        return m_collider->getCollider();
    }

    CShape MapCollider::getCollider() const
    {
        if (m_colliderCache) {
            return m_colliderCache.value();
        }
        return this->calcCollider(); 
    }

    void MapCollider::onPrePhysics()
    {
        if (m_foot) {
            m_foot->reset();
        }
        m_result->onReflesh();
        
        m_colliderCache = this->calcCollider();
    }

    //void MapCollider::onCollision(const Ref<Terrain>& terrain)
    //{
    //    if (!m_isThrough && m_useBody) {
    //        auto col = m_body->fixPos(terrain->getMapColInfo());
    //        m_result->add(col);

    //        if (m_foot) {
    //            if (col.isUp()) {
    //                m_foot->apply(Foot::Landing);
    //            }

    //            // Ladder情報があれば保持
    //            terrain->isThen<Tag::Ladder, Map::Ladder::LadderProxy>([this](const Map::Ladder::LadderProxy& ladder) {
    //                m_foot->updateLadderInfo({
    //                    .pos = ladder.getCenterTopPos()
    //                });
    //                if (ladder.getCenterLine().intersects(m_body->region())) {
    //                    auto state = ladder.isTop() ? Foot::LadderTop : Foot::Ladder;
    //                    m_foot->apply(state);
    //                    return true;
    //                }
    //                return false;
    //            });
    //            // PenetrateFloor情報保持
    //            if (col.isUp()) {
    //                terrain->isThen<
    //                    Tag::PenetrateFloor,
    //                    Map::PenetrateFloor::PenetrateFloorProxy
    //                >([this, col](const Map::PenetrateFloor::PenetrateFloorProxy& floor) {
    //                    if (floor.tryDown(m_body->region())) {
    //                        m_foot->apply(Foot::Downable);
    //                        return true;
    //                    }
    //                    return false;
    //                });
    //            }
    //        }
    //    }

    //    m_result->add(terrain);
    //}
    void MapCollider::onPostPhysics()
    {
        if (!m_useBody) {
            return;
        }
        if (!m_isEnableRoomHit) {
            return;
        }
        // ルーム壁との衝突
        auto col = m_body->fixPos(m_pActor->getModule<Camera>()->getCurrentRoom(), m_roomHitStrict);
        m_result->add(col);
    }
    bool MapCollider::isHitGround() const
    {
        return m_result->isHitGround();
    }
    bool MapCollider::isHitWall() const
    {
        return m_result->isHitWall();
    }
    bool MapCollider::isHitForwardWall() const
    {
        return m_result->isHitWall(m_body->getForward());
    }
    bool MapCollider::isHitAny() const
    {
        return m_result->isHitAny();
    }
    //const s3d::Array<Ref<Terrain>>& MapCollider::getHitTerrains() const
    //{
    //    return m_result->getResults();
    //}
    //s3d::Array<ActorObj*> MapCollider::getHitActors() const
    //{
    //    return m_result->getHitActors();
    //}
}
