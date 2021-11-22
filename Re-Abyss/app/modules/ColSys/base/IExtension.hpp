#pragma once
#include <any>

namespace abyss::ColSys
{
	struct ExtData
	{
		ExtData() = default;
		template<class T>
		ExtData(T&& value) :
			m_value(std::forward<T>(value))
		{}

		template<class T>
		T get() const
		{
			return std::any_cast<T>(m_value);
		}
	private:
		std::any m_value;
	};

	/// <summary>
	/// 拡張
	/// </summary>
	class IExtension
	{
	public:
		virtual ~IExtension() = default;
		virtual ExtData data() const = 0;
	};
}