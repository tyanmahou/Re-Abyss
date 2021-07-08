#include "IdGenerator.hpp"
#include <limits>

namespace abyss
{
    s3d::uint64 IdGenerator::createId()
    {
        if (!m_freeId.empty()) {
            auto id = m_freeId.front();
            m_freeId.pop();
            return id;
        }
        if (m_nextId == std::numeric_limits<s3d::uint64>::max()) {
            auto id = m_nextId;
            m_nextId = 0;
            return id;
        }
        return m_nextId++;
    }

    void IdGenerator::releaseId(s3d::uint64 id)
    {
        m_freeId.push(id);
    }

    void IdGenerator::reset()
    {
        m_nextId = 0;
        std::queue<s3d::uint64> empty;
        m_freeId.swap(empty);
    }
}
