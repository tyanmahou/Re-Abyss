#include <abyss/components/Effect/Actor/Player/ShotFiring/Builder.hpp>
#include <abyss/components/Effect/Actor/Player/ShotFiring/Main.hpp>
#include <abyss/modules/Effect/base/EffectObj.hpp>

namespace abyss::Effect::Actor::Player::ShotFiring
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