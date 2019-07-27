#include "AbyssDream.hpp"
#include<Siv3D/String.hpp>
#include<Siv3D/Vector2D.hpp>

namespace abyss
{
	bool AbyssDream::update() const
	{
		return true;
	}

	AbyssDream::AbyssDream():
		Application(L"Abyss Dream", {960, 540})
	{
	}

	AbyssDream::~AbyssDream()
	{
	}
}
