#include "MapColliderModel.hpp"
#include <abyss/controllers/Actors/base/IActor.hpp>

#include <abyss/models/Actors/Commons/BodyModel.hpp>
#include <abyss/models/Actors/Commons/TerrainModel.hpp>
#include <abyss/controllers/Camera/Camera.hpp>

namespace abyss
{
    class MapColliderModel::Result
    {
    private:
        s3d::Array<Ref<TerrainModel>> m_results;
        ColDirection m_col;
    public:
        Result() = default;

        void add(ColDirection col)
        {
            m_col |= col;
        }

        void add(const Ref<TerrainModel>& terrain)
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

        const s3d::Array<Ref<TerrainModel>>& getResults() const
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

    MapColliderModel::MapColliderModel(IActor* pActor):
        IPhysicsModel(pActor),
        m_result(std::make_unique<Result>())
    {}
    void MapColliderModel::setup()
    {
        m_body = m_pActor->find<BodyModel>();
    }

    s3d::RectF MapColliderModel::getCollider() const
    {
        return m_body->region();
    }

    void MapColliderModel::onPrePhysics()
    {
        m_result->onReflesh();
    }

    void MapColliderModel::onCollision(const Ref<TerrainModel>& terrain)
    {
        if (!m_isThrough) {
            auto col = m_body->fixPos(terrain->getMapColInfo());
            m_result->add(col);
        }

        m_result->add(terrain);
    }
    void MapColliderModel::onLastPhysics()
    {
        if (!m_enableRoomHit) {
            return;
        }
        // ルーム壁との衝突
        auto col = m_body->fixPos(m_pActor->getModule<Camera>()->getCurrentRoom());
        m_result->add(col);
    }
    bool MapColliderModel::isHitGround() const
    {
        return m_result->isHitGround();
    }
    bool MapColliderModel::isHitWall() const
    {
        return m_result->isHitWall();
    }
    bool MapColliderModel::isHitForwardWall() const
    {
        return m_result->isHitWall(m_body->getForward());
    }
    bool MapColliderModel::isHitAny() const
    {
        return m_result->isHitAny();
    }
    const s3d::Array<Ref<TerrainModel>>& MapColliderModel::getHitTerrains() const
    {
        return m_result->getResults();
    }
    s3d::Array<IActor*> MapColliderModel::getHitActors() const
    {
        return m_result->getHitActors();
    }
}
