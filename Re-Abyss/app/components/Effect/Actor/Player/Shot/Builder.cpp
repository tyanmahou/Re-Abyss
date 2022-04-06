#include <abyss/components/Effect/Actor/Player/Shot/Builder.hpp>
#include <abyss/components/Effect/Actor/Player/Shot/Main.hpp>
#include <abyss/modules/Effect/base/EffectObj.hpp>

namespace abyss::Effect::Actor::Player::Shot
{
	void Builder::Build(
		EffectObj* pObj,
		const s3d::Vec2& pos,
		double radius,
		const s3d::ColorF& color
	) {
		pObj->attach<Main>(pObj, pos, radius, color);
	}
}