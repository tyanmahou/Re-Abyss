#pragma once
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/types/Forward.hpp>

namespace abyss::Actor::Enemy::LaunShark::Shot
{
	class ShotActor :
		public IActor
	{
	private:
		Ref<Body> m_body;
		Ref<RotateCtrl> m_rotate;
	public:
		ShotActor(const s3d::Vec2& pos, Forward forward);
		CShape getCollider() const;
		s3d::Quad getColliderQuad() const;

		bool accept(const ActVisitor& visitor) override;
	};
}