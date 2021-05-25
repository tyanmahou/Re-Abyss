#pragma once
#include <memory>

namespace abyss
{
	class Game
	{
	public:
		Game();
		~Game();
		bool update();
	private:
		class Impl;
		std::unique_ptr<Impl> m_pImpl;
	};
}