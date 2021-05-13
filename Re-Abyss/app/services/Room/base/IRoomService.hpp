#pragma once
#include <Siv3D/Array.hpp>
#include <abyss/commons/Fwd.hpp>

namespace abyss
{
	class IRoomService
	{
	public:
		virtual ~IRoomService() = default;
		virtual const s3d::Array<RoomEntity>& getRooms() const = 0;
	};
}