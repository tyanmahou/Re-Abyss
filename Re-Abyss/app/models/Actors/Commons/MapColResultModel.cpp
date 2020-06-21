#include "MapColResultModel.hpp"
#include <abyss/models/Actors/Commons/TerrainModel.hpp>

namespace  abyss
{
    MapColResultModel::MapColResultModel(IActor* pActor):
        m_pActor(pActor)
    {}
    void MapColResultModel::add(ColDirection col)
    {
        m_col |= col;
    }
    void MapColResultModel::add(const Ref<TerrainModel>& terrain, ColDirection col)
    {
        m_results.push_back(terrain);
        m_col |= col;
    }
    void MapColResultModel::onPrePhysics()
    {
        m_results.clear();
        m_col = ColDirection::None;
    }
    bool MapColResultModel::isHitGround() const
    {
        return m_col.isUp();
    }
    bool MapColResultModel::isHitWall() const
    {
        return m_col.isLeft() || m_col.isRight();
    }
    bool MapColResultModel::isHitWall(Forward forward) const
    {
        if (forward == Forward::Left && m_col.isRight()) {
            return true;
        }
        if (forward == Forward::Right && m_col.isLeft()) {
            return true;
        }
        return false;
    }
    bool MapColResultModel::isHitAny() const
    {
        return !m_results.empty();
    }
    s3d::Array<IActor*> MapColResultModel::getHitActors() const
    {
        s3d::Array<IActor*> ret;
        for (const auto& terrain : m_results) {
            if (terrain) {
                ret.push_back(terrain->getActor());
            }
        }
        return ret;
    }
}
