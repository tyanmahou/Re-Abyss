#pragma once
#include <memory>
#include <abyss/utils/DebugMenu/ISkin.hpp>

namespace abyss::DebugMenu
{
	class Root
	{
	public:
		Root();

		void draw() const;
	private:
		std::unique_ptr<ISkin> m_skin;
	};
}