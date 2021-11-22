#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/ColSys/base/IExtension.hpp>
#include <Siv3D/Vector2D.hpp>

namespace abyss::Actor::Col
{
	class Attacker final : public ColSys::IExtension
	{
	public:
		struct Data
		{
			s3d::int32 power{ 1 };
			s3d::Vec2 pos{};
			s3d::Vec2 velocity{};
		};
	public:
		Attacker(ActorObj* pActor, s3d::int32 power);

		ColSys::ExtData data() const override;
	private:
		ActorObj* m_pActor;
		s3d::int32 m_power = 1;
	};
}