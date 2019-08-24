#include "AbyssDream.hpp"
#include "Game.hpp"

#include <Siv3D/Vector2D.hpp>
#include <Siv3D/String.hpp>

namespace abyss
{
	bool AbyssDream::update() const
	{
		return Game::Update();
	}

	AbyssDream::AbyssDream():
		Application(L"Abyss Dream", {960, 540})
	{}

	AbyssDream::~AbyssDream()
	{
	}
}
