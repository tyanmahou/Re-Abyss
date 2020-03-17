#pragma once

# include <memory>
# include <abyss/utils/Singleton.hpp>

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