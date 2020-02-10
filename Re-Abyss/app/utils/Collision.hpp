#pragma once

#include <tuple>
#include <Siv3D/Fwd.hpp>

#include <abyss/commons/Fwd.hpp>

namespace abyss
{
	[[nodiscard]] bool Intersects(const CShape& a, const CShape& b);
}