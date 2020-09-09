#include "MapCollider.hpp"
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/controllers/Actors/ActInclude.hpp>

#include <abyss/models/Actors/Commons/BodyModel.hpp>
#include <abyss/components/Actors/Commons/Foot.hpp>
#include <abyss/components/Actors/Commons/Terrain.hpp>
#include <abyss/controllers/Camera/Camera.hpp>

namespace abyss::Actor
{
    class MapCollider::Result
    {
    private:
        s3d::Array<Ref<Terrain>> m_results;
        ColDirection m_col;
    public:
        Result() = default;

        void add(ColDirection col)
        {
            m_col |= col;
        }

        void add(const Ref<Terrain>& terrain)
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
            return !m_results.empty();
        }

        const s3d::Array<Ref<Terrain>>& getResults() const
        {
            return m_results;
        }

        s3d::Array<IActor*> getHitActors() const
        {
            s3d::Array<IActor*> ret;
            for (const auto& terrain : m_results) {
                if (terrain) {
                    ret.push_back(terrain->getActor());
                }
            }
            return ret;
        }
    };

    MapCollider::MapCollider(IActor* pActor):
        IPhysicsModel(pActor),
        m_result(std::make_unique<Result>())
    {}
    void MapCollider::setup()
    {
        m_body = m_pActor->find<BodyModel>();
        m_foot = m_pActor->find<Foot>();
    }

    s3d::RectF MapCollider::getCollider() const
    {
        return m_body->region();
    }

    void MapCollider::onPrePhysics()
    {
        if (m_foot) {
            m_foot->reset();
        }
        m_result->onReflesh();
    }

    void MapCollider::onCollision(const Ref<Terrain>& terrain)
    {
        if (!m_isThrough) {
            auto col = m_body->fixPos(terrain->getMapColInfo());
            m_result->add(col);

            if (m_foot) {
                if (col.isUp()) {
                    m_foot->apply(Foot::Landing);
                }
                terrain->accept(overloaded{
                    [this](const Actor::Map::Ladder::LadderActor& ladder) {
                        if (ladder.getCenterLine().intersects(m_body->region())) {
                            m_foot->setLadderPosX(ladder.getPos().x);
                            auto state = ladder.isTop() ? Foot::LadderTop : Foot::Ladder;
                            m_foot->apply(state);
                        }
                    }
                });
            }
        }

        m_result->add(terrain);
    }
    void MapCollider::onLastPhysics()
    {
        if (!m_isEnableRoomHit) {
            return;
        }
        // ルーム壁との衝突
        auto col = m_body->fixPos(m_pActor->getModule<Camera>()->getCurrentRoom(), m_isEnableRoomHitStrict);
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
    bool MapCollider::acceptAll(const ActVisitor& visitor)
    {
        bool result = false;
        for (const auto& terrain : this->getHitTerrains()) {
            if (!terrain) {
                continue;
            }
            result |= terrain->accept(visitor);
        }

        return result;
    }
    const s3d::Array<Ref<Terrain>>& MapCollider::getHitTerrains() const
    {
        return m_result->getResults();
    }
    s3d::Array<IActor*> MapCollider::getHitActors() const
    {
        return m_result->getHitActors();
    }
}
