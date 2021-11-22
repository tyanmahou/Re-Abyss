#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/Collision/base/IExtension.hpp>
#include <Siv3D/Vector2D.hpp>

namespace abyss::Actor::Collision
{
	class Attacker final : public abyss::Collision::IExtension
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

		abyss::Collision::ExtData data() const override;
	private:
		ActorObj* m_pActor;
		s3d::int32 m_power = 1;
	};
}