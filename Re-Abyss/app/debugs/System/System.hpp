#pragma once
#if ABYSS_DEBUG
#include <memory>
#include <functional>

namespace abyss::Debug
{
	/// <summary>
	/// デバッグシステム
	/// </summary>
	class System
	{
	public:
		System();
		~System();

		bool apply(std::function<bool()> callback);
	private:
		class Impl;
		std::unique_ptr<Impl> m_pImpl;
	};
}
#endif