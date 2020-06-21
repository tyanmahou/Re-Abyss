#include "MapColliderModel.hpp"
#include <abyss/controllers/Actors/base/IActor.hpp>

#include <abyss/models/Actors/Commons/BodyModel.hpp>
#include <abyss/models/Actors/Commons/MapColResultModel.hpp>
#include <abyss/models/Actors/Commons/TerrainModel.hpp>
#include <abyss/debugs/Log/Log.hpp>
namespace abyss
{
    void MapColliderModel::setup()
    {
        m_body = m_pActor->find<BodyModel>();
        m_result = m_pActor->find<MapColResultModel>();
    }

    s3d::RectF MapColliderModel::getCollider() const
    {
        return m_body->region();
    }

    void abyss::MapColliderModel::onCollision(const Ref<TerrainModel>& terrain)
    {
        auto col = m_body->fixPos(terrain->getMapColInfo());
        Debug::Log::Print << (s3d::uint8)terrain->getMapColInfo().col <<U"," << (s3d::uint8)col;
        if (m_result) {
            m_result->add(terrain, col);
        }
    }
}
