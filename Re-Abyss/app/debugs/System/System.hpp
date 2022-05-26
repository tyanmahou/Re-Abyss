#pragma once
#if ABYSS_DEBUG
#include <memory>

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

		void update();
		void draw() const;

		bool isPause() const;
	private:
		class Impl;
		std::unique_ptr<Impl> m_pImpl;
	};
}
#endif