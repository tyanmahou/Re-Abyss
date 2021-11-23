#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/ColSys/base/IExtension.hpp>
#include <Siv3D/Vector2D.hpp>

namespace abyss::Actor::Col
{
	class Mover final : public ColSys::IExtension
	{
	public:
		struct Data
		{
			s3d::Vec2 pos{};
			s3d::Vec2 velocity{};
		};
	public:
		Mover(ActorObj* pActor);

		ColSys::ExtData data() const override;
	private:
		ActorObj* m_pActor;
	};
}