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
		void draw() const override;
		s3d::Shape getCollider() const override;
		void onCollisionStay(ICollider* col) override;
		bool isDelete() const override;

		s3d::Circle getColliderCircle() const;

		Type getType() const;
		Forward getForward() const;
		const Vec2& getPos() const;

	};
}