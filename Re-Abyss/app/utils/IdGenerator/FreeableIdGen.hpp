#pragma once
#include <Siv3D/Types.hpp>
#include <queue>
#include <limits>

namespace abyss
{
    /// <summary>
    /// Id生成器
    /// </summary>
    template<class Type = s3d::uint64>
    class FreeableIdGen
    {
    public:
        using value_type = Type;
    public:
        /// <summary>
        /// Idの生成
        /// </summary>
        /// <returns></returns>
        value_type createId()
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

        /// <summary>
        /// Idの開放
        /// </summary>
        /// <param name="id"></param>
        void releaseId(value_type id)
        {
            m_freeIds.push(id);
        }

        /// <summary>
        /// リセット
        /// </summary>
        void reset()
        {
            m_nextId = 0;

            // queue clear
            std::queue<value_type> empty;
            m_freeIds.swap(empty);
        }
    private:
        value_type m_nextId = 0;
        std::queue<value_type> m_freeIds;
    };

    using FreeableIdGenU64 = FreeableIdGen<>;
}