#pragma once
#include <Siv3D/String.hpp>
#include <array>

namespace abyss
{
	template<size_t Size>
	struct TrivialString
	{
        using string_type = s3d::String;
        using string_view_type = s3d::StringView;
        using value_type = typename string_type::value_type;
        static_assert(std::is_same_v<typename string_type::value_type, typename string_view_type::value_type>);

		TrivialString() = default;
		TrivialString(const string_type& other)
		{
			m_length = s3d::Min<size_t>(Size, other.size());
			for (size_t index = 0; index < m_length; ++index) {
				m_str[index] = other[index];
			}
		}
		TrivialString(string_view_type other)
		{
			m_length = s3d::Min<size_t>(Size, other.size());
			for (size_t index = 0; index < m_length; ++index) {
				m_str[index] = other[index];
			}
		}
        TrivialString(const value_type* other):
            TrivialString(string_view_type(other))
        {
        }
		operator string_type() const
		{
			return toString();
		}
        string_type toString() const
		{
			return string_type(m_str.data(), m_length);
		}
        string_view_type toStringView() const
        {
            return string_view_type(m_str.data(), m_length);
        }
        const value_type* data() const
        {
            return m_str.data();
        }
	private:
		std::array<char32_t, Size> m_str;
		size_t m_length;
	};

	using TrivialString32 = TrivialString<32>;
	using TrivialString64 = TrivialString<64>;
	using TrivialString128 = TrivialString<128>;
	using TrivialString256 = TrivialString<256>;
	using TrivialString512 = TrivialString<512>;

    static_assert(std::is_trivial_v<TrivialString32>);
}
