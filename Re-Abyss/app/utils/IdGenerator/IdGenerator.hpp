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
        /// <summary>
        /// Idの生成
        /// </summary>
        /// <returns></returns>
        s3d::uint64 createId();

        /// <summary>
        /// Idの開放
        /// </summary>
        /// <param name="id"></param>
        void releaseId(s3d::uint64 id);

        /// <summary>
        /// リセット
        /// </summary>
        void reset();
    private:
        s3d::uint64 m_nextId = 0;
        std::queue<s3d::uint64> m_freeId;
    };
}