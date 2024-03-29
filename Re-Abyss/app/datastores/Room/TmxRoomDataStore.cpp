#include <abyss/datastores/Room/TmxRoomDataStore.hpp>

#include <abyss/utils/Collision/ColDirection.hpp>
#include <abyss/datastores/base/parser/TmxParseUtil.hpp>

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
					passbleBits |= ColDirection::Up;
				}
				if (obj.getProperty(U"down").value_or(false)) {
					passbleBits |= ColDirection::Down;
				}
				if (obj.getProperty(U"left").value_or(false)) {
					passbleBits |= ColDirection::Left;
				}
				if (obj.getProperty(U"right").value_or(false)) {
					passbleBits |= ColDirection::Right;
				}
				s3d::Optional<s3d::ColorF> lightColor;
				if (auto c = obj.getProperty(U"light_color")) {
					lightColor = s3d::ColorF(c->toColor());
				}
				ret.push_back({ 
					obj.id,
					obj.toRectF(),
					passbleBits,
					lightColor
					});
			}
		};

		TmxParseUtil::ParseForGroup(*layer, parser);

		return ret;
    }
}
