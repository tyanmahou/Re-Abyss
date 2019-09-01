#pragma once
#include "WorldObject.hpp"
#include "../../../application/types/Physics.hpp"

namespace abyss
{
	class PlayerShotModel : public WorldObject
	{
	public:
		enum class Type
		{
			Normal,
			Small,
			Medium,
			Big,
		};
	private:
		Type m_type;
		Physics m_body;
	public:
		PlayerShotModel(const s3d::Vec2& pos, Forward forward, s3d::int32 charge);
		void start() override;
		void update(double dt) override;
		CShape getCollider() const override;
		void onCollisionStay(ICollider* col) override;

		s3d::Circle getColliderCircle() const;

		Type getType() const;
		Forward getForward() const;
		const s3d::Vec2& getPos() const;

	};
}