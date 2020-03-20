#pragma once
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <Siv3D/Vector2D.hpp>

namespace abyss
{
    class SlimeSenser : public IActor
    {
		s3d::Vec2 m_pos;
		bool m_onCollision = true;
		SlimeActor* m_parent;
	public:
		SlimeSenser(SlimeActor* p) :
			m_parent(p)
		{}
		void update(double)override;
		void draw() const override;
		CShape getCollider() const override;

		void onCollisionStay(ICollider* col) override;
    };
}