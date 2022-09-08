#include <abyss/modules/Stage/StartPos/StartPosContainer.hpp>

namespace abyss
{
    void StartPosContainer::add(const StartPos& startPos)
    {
        m_container[startPos.getStartId()] = startPos;
    }

    s3d::Optional<StartPos> StartPosContainer::find(s3d::int32 startId) const
    {
        if (auto it = m_container.find(startId); it != m_container.end()) {
            return it->second;
        }
        return s3d::none;
    }

}
