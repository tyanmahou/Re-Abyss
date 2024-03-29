#include <abyss/components/Actor/Common/MapCollider.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>

#include <abyss/components/Actor/Common/Collider.hpp>
#include <abyss/components/Actor/Common/Body.hpp>
#include <abyss/components/Actor/Common/Foot.hpp>
#include <abyss/components/Actor/Land/Ladder/LadderUtil.hpp>
#include <abyss/components/Actor/Land/PenetrateFloor/PenetrateFloorExtension.hpp>

#include <abyss/modules/Room/RoomManager.hpp>
#include <abyss/modules/Physics/PhysicsManager.hpp>
#include <abyss/modules/Physics/base/IContacter.hpp>
#include <abyss/modules/Physics/base/TerrainData.hpp>
#include <abyss/utils/Collision/SweepUtil.hpp>
#include <abyss/utils/Collision/CShape.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>

namespace abyss::Actor
{
    class MapCollider::Result
    {
    private:
        s3d::Array<Physics::TerrainData> m_results;
        ColDirection m_col;
    public:
        Result() = default;

        void add(ColDirection col)
        {
            m_col |= col;
        }

        void add(const Physics::TerrainData& terrain)
        {
            m_results.push_back(terrain);
        }
        void onReflesh()
        {
            m_results.clear();
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
            if (forward.isLeft() && m_col.isRight()) {
                return true;
            }
            if (forward.isRight() && m_col.isLeft()) {
                return true;
            }
            return false;
        }

        bool isHitAny() const
        {
            return !m_results.empty();
        }

        const s3d::Array<Physics::TerrainData>& getHitTerrains() const
        {
            return m_results;
        }
    };
    class MapCollider::Contacter final : public Physics::IContacter
    {
    public:
        Contacter(ActorObj* pActor, bool useBody) :
            m_pActor(pActor),
            m_result(std::make_unique<Result>()),
            m_useBody(useBody)
        {}
    public:
        void onStart()
        {
            m_body = m_pActor->find<Body>();
            m_collider = m_pActor->find<Collider>()->main();
            m_foot = m_pActor->find<Foot>();
        }

        void onEnd()
        {

        }

        void onPrePhysics()
        {
            if (m_foot) {
                m_foot->reset();
            }
            m_result->onReflesh();

            m_shape = this->calcCollider();
        }

        void onCollision(const Physics::TerrainData& terrain) override
        {
            if (!m_isThrough && m_useBody) {
                auto col = m_body->fixPos(terrain);
                m_result->add(col);

                if (m_foot) {
                    if (col.isUp()) {
                        m_foot->apply(Foot::Landing);
                    }

                    // Ladder情報があれば保持
                    if (terrain.tag.is<Physics::Tag::Ladder>()) {
                        using Land::Ladder::LadderUtil;
                        m_foot->updateLadderInfo({
                            .pos = LadderUtil::CenterTopPos(terrain)
                        });

                        if (LadderUtil::CenterLine(terrain).intersects(m_body->region())) {
                            auto state = LadderUtil::IsTop(terrain) ? Foot::LadderTop : Foot::Ladder;
                            m_foot->apply(state);
                        }
                    }
                    // PenetrateFloor情報保持
                    if (col.isUp()) {
                        using Land::PenetrateFloor::PenetrateFloorExtension;

                        terrain.isThen<
                            Physics::Tag::PenetrateFloor,
                            PenetrateFloorExtension
                        >([this, &terrain, col](const PenetrateFloorExtension& floor) {
                            if (floor.tryDown(terrain, m_body->region())) {
                                m_foot->apply(Foot::Downable);
                                return true;
                            }
                            return false;
                        });
                    }
                }
            }

            m_result->add(terrain);
        }

        void onPostPhysics()
        {
            if (!m_useBody) {
                return;
            }
            if (!m_isEnableRoomHit) {
                return;
            }
            // ルーム壁との衝突
            auto col = m_body->fixPos(m_pActor->getModule<RoomManager>()->currentRoom(), m_roomHitStrict);
            m_result->add(col);
        }
    public:
        void setId(s3d::uint64 id) override
        {
            m_id = id;
        }
        s3d::uint64 id() const override
        {
            return m_id;
        }

        bool isActive() const override
        {
            return !m_isDestroyed && m_pActor->isActive();
        }

        void destroy()
        {
            m_isDestroyed = true;
        }

        bool isDestroyed() const override
        {
            return m_isDestroyed;
        }

        CShape calcCollider() const
        {
            CShape shape = m_useBody ? m_body->region() : m_collider->getCollider();
            return !m_isEnableTrajectory ? shape :
                SweepUtil::Sweep(shape, -m_body->moveDiff());
        }

        const CShape& getShape() const override
        {
            return m_shape;
        }

        void setIsEnableRoomHit(bool enable, const s3d::Optional<ColDirection>& strict = s3d::none)
        {
            m_isEnableRoomHit = enable;
            m_roomHitStrict = strict;
        }

        void setIsThrough(bool isThrough)
        {
            m_isThrough = isThrough;
        }

        void setIsEnableTrajectory(bool enable)
        {
            m_isEnableTrajectory = enable;
        }

        bool isHitGround() const
        {
            return m_result->isHitGround();
        }

        bool isHitWall() const
        {
            return m_result->isHitWall();
        }
        bool isHitForwardWall() const
        {
            return m_result->isHitWall(m_body->getForward());
        }
        bool isHitAny() const
        {
            return m_result->isHitAny();
        }
        const s3d::Array<Physics::TerrainData>& getHitTerrains() const
        {
            return m_result->getHitTerrains();
        }
    private:
        ActorObj* m_pActor;
        bool m_isDestroyed = false;
        s3d::uint64 m_id = 0;
        CShape m_shape;
        std::unique_ptr<Result> m_result;
    private:
        Ref<Body> m_body;
        Ref<Col::ICollider> m_collider;
        Ref<Foot> m_foot;

        bool m_isEnableRoomHit = false;
        s3d::Optional<ColDirection> m_roomHitStrict;
        bool m_isThrough = false; // すりぬけるか
        bool m_useBody = true;
        bool m_isEnableTrajectory = false;
    };

    MapCollider::MapCollider(ActorObj* pActor, bool useBody) :
        m_pActor(pActor),
        m_contacter(std::make_shared<Contacter>(pActor, useBody))
    {}
    void MapCollider::onStart()
    {
        m_pActor->getModule<PhysicsManager>()->regist(m_contacter);
        m_contacter->onStart();
    }

    void MapCollider::onEnd()
    {
        m_contacter->onEnd();
        m_contacter->destroy();
    }

    void MapCollider::onPrePhysics()
    {
        m_contacter->onPrePhysics();
    }

    void MapCollider::onPostPhysics()
    {
        m_contacter->onPostPhysics();
    }
    MapCollider& MapCollider::setIsEnableRoomHit(bool enable, const s3d::Optional<ColDirection>& strict)
    {
        m_contacter->setIsEnableRoomHit(enable, strict);
        return *this;
    }
    MapCollider& MapCollider::setIsThrough(bool isThrough)
    {
        m_contacter->setIsThrough(isThrough);
        return *this;
    }
    MapCollider& MapCollider::setIsEnableTrajectory(bool enable)
    {
        m_contacter->setIsEnableTrajectory(enable);
        return *this;
    }
    bool MapCollider::isHitGround() const
    {
        return m_contacter->isHitGround();
    }
    bool MapCollider::isHitWall() const
    {
        return m_contacter->isHitWall();
    }
    bool MapCollider::isHitForwardWall() const
    {
        return m_contacter->isHitForwardWall();
    }
    bool MapCollider::isHitAny() const
    {
        return m_contacter->isHitAny();
    }
    const s3d::Array<Physics::TerrainData>& MapCollider::getHitTerrains() const
    {
        return m_contacter->getHitTerrains();
    }
}
