#include "TmxRoomDataStore.hpp"
#include <abyss/types/Forward.hpp>

namespace abyss
{
	using namespace s3d;
	using namespace s3dTiled;

    s3d::Array<RoomEntity> TmxRoomDataStore::select() const
    {
		s3d::Array<RoomEntity> ret;

		// 部屋情報取得
		auto layer = m_tmx.getLayer(U"room");
		if (!layer) {
			return ret;
		}
		auto parser = [&ret](const ObjectGroup& layer) {
			for (const auto& obj : layer.getObjects()) {

				s3d::uint8 passbleBits = 0;
				if (obj.getProperty(U"up").value_or(false)) {
					passbleBits |= static_cast<uint8>(Forward::Up);
				}
				if (obj.getProperty(U"down").value_or(false)) {
					passbleBits |= static_cast<uint8>(Forward::Down);
				}
				if (obj.getProperty(U"left").value_or(false)) {
					passbleBits |= static_cast<uint8>(Forward::Left);
				}
				if (obj.getProperty(U"right").value_or(false)) {
					passbleBits |= static_cast<uint8>(Forward::Right);
				}
				ret.push_back({ obj.id, obj.toRectF(), passbleBits });
			}
		};
		layer->then(parser);
		return ret;
    }
}
