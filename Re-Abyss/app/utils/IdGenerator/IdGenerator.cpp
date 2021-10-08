#include "IdGenerator.hpp"
#include <limits>

namespace abyss
{
    IdGenerator::value_type IdGenerator::createId()
    {
        if (!m_freeIds.empty()) {
            auto id = m_freeIds.front();
            m_freeIds.pop();
            return id;
        }
        if (m_nextId == std::numeric_limits<value_type>::max()) [[unlikely]] {
            // アサートでもいい
            auto id = m_nextId;
            m_nextId = 0;
            return id;
        }
        return m_nextId++;
    }

    void IdGenerator::releaseId(value_type id)
    {
        m_freeIds.push(id);
    }

    void IdGenerator::reset()
    {
        m_nextId = 0;

        // queue clear
        std::queue<value_type> empty;
        m_freeIds.swap(empty);
    }
}
