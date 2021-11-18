#pragma once
#include <Siv3D/Types.hpp>

namespace abyss
{
    /// <summary>
    /// Id生成器
    /// </summary>
	template<class Type = s3d::uint64>
	class IdGen
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
            return m_nextId++;
        }

        /// <summary>
        /// リセット
        /// </summary>
        void reset()
        {
            m_nextId = 0;
        }
    private:
        value_type m_nextId = 0;
	};

    using IdGenU64 = IdGen<>;
}