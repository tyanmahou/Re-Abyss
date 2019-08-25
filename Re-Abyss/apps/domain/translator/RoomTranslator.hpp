#pragma once

namespace abyss
{
	class RoomModel;
	struct RoomEntity;

	class RoomTranslator
	{
	public:
		RoomModel create(const RoomEntity& entity) const;
	};
}
