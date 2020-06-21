#include "MapColResult.hpp"

namespace  abyss
{
    MapColResultModel::MapColResultModel(IActor* pActor):
        m_pActor(pActor)
    {}
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
}
