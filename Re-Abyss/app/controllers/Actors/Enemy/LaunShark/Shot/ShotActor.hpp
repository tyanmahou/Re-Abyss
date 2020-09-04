#pragma once
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/controllers/Actors/base/Attacker.hpp>
#include <abyss/controllers/Actors/base/Receiver.hpp>
#include <abyss/types/Forward.hpp>

namespace abyss::Actor::LaunShark::Shot
{
	class ShotActor :
		public IActor,
		public Attacker,
		public Receiver
	{
	private:
		Ref<BodyModel> m_body;
		Ref<RotateModel> m_rotate;
	public:
		ShotActor(const s3d::Vec2& pos, Forward forward);
		CShape getCollider() const;
		s3d::Quad getColliderQuad() const;

		bool accept(const ActVisitor& visitor) override;
	};
}