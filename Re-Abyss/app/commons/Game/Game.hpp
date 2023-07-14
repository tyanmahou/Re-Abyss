#pragma once
#include <memory>

namespace abyss
{
	class Game
	{
	public:
		Game();
		~Game();
        void onStart();
        bool update();
        void onEnd();
	private:
		class Impl;
		std::unique_ptr<Impl> m_pImpl;
	};
}
