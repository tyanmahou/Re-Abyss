#pragma once
#include <Siv3D/String.hpp>
#include <array>

namespace abyss
{
	template<size_t Size>
	struct TrivialString
	{
		TrivialString() = default;
		TrivialString(const s3d::String& other)
		{
			m_length = s3d::Min<size_t>(Size, other.size());
			for (size_t index = 0; index < m_length; ++index) {
				m_str[index] = other[index];
			}
		}
		TrivialString(s3d::StringView other)
		{
			m_length = s3d::Min<size_t>(Size, other.size());
			for (size_t index = 0; index < m_length; ++index) {
				m_str[index] = other[index];
			}
		}
		operator s3d::String() const
		{
			return toStr();
		}
		s3d::String toStr() const
		{
			return s3d::String(m_str.data(), m_length);
		}
	private:
		std::array<char32_t, Size> m_str{};
		size_t m_length = 0;
	};

	using TrivialString32 = TrivialString<32>;
	using TrivialString64 = TrivialString<64>;
	using TrivialString128 = TrivialString<128>;
	using TrivialString256 = TrivialString<256>;
	using TrivialString512 = TrivialString<512>;
}