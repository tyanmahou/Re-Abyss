#pragma once
#include <Siv3D/Fwd.hpp>
#include <queue>

namespace abyss
{
    /// <summary>
    /// Id生成器
    /// </summary>
    class IdGenerator
    {
    public:
        using value_type = s3d::uint64;
    public:
        /// <summary>
        /// Idの生成
        /// </summary>
        /// <returns></returns>
        value_type createId();

        /// <summary>
        /// Idの開放
        /// </summary>
        /// <param name="id"></param>
        void releaseId(value_type id);

        /// <summary>
        /// リセット
        /// </summary>
        void reset();
    private:
        value_type m_nextId = 0;
        std::queue<value_type> m_freeIds;
    };
}