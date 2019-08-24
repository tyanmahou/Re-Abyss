#pragma once

#include "../util/Singleton.hpp"
#include <memory>

namespace abyss
{
	class Game : protected Singleton<Game>
	{
		friend Singleton < Game >;
	private:
		class Impl;
		std::shared_ptr<Impl> m_pImpl;

		Game();
	public:
		static bool Update();
	};
}