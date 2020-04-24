#pragma once
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <Siv3D/Vector2D.hpp>

namespace abyss::Slime
{
	class SlimeActor;

    class Senser : public IActor
    {
		s3d::Vec2 m_pos;
		bool m_onCollision = true;
		SlimeActor* m_parent;
	public:
		Senser(SlimeActor* p) :
			m_parent(p)
		{}
		void update(double)override;
		void draw() const override;
		CShape getCollider() const override;

		void onCollisionStay(ICollider* col) override;
    };
}