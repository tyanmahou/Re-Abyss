#pragma once
// https://github.com/Siv3D/OpenSiv3D/blob/main/Siv3D/src/Siv3D/Input/InputState.hpp

# pragma once
# include <Siv3D/Common.hpp>
# include <Siv3D/Stopwatch.hpp>

namespace s3d
{
	struct InputState
	{
		static constexpr size_t KeyCount = 256;

		static constexpr size_t MouseButtonCount = 8;

		Duration pressedDuration{ 0 };

		Stopwatch stopwatch;

		bool up = false;

		bool pressed = false;

		bool down = false;

		void update(bool currentPressed);

		void clear();
	};
}