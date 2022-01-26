#include <abyss/models/Actor/Gimmick/StartPos/StartPosListModel.hpp>

namespace abyss
{
    void StartPosListModel::add(const StartPosModel& startPos)
    {
        m_startPoss[startPos.getStartId()] = startPos;
    }

    s3d::Optional<StartPosModel> StartPosListModel::find(s3d::int32 startId) const
    {
        if (m_startPoss.find(startId) != m_startPoss.end()) {
            return m_startPoss.at(startId);
        }
        return s3d::none;
    }

}
