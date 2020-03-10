#pragma once
#include <abyss/models/actors/base/IActor.hpp>
#include <abyss/types/Physics.hpp>
#include <abyss/views/actors/Player/Shot/PlayerShotView.hpp>

namespace abyss
{
	class PlayerShotActor : 
		public IActor,
		public PlayerShotView
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
		PlayerShotActor(const s3d::Vec2& pos, Forward forward, s3d::int32 charge);
		void start() override;
		void update(double dt) override;
		CShape getCollider() const override;
		void onCollisionStay(ICollider* col) override;

		s3d::Circle getColliderCircle() const;

		Type getType() const;
		Forward getForward() const;
		const s3d::Vec2& getPos() const;

		void accept(const ActVisitor& visitor) override;
		void draw() const override;
	};
}