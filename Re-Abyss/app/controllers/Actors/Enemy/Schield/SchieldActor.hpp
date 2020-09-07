#pragma once
#include <abyss/controllers/Actors/Enemy/EnemyActor.hpp>
#include <abyss/commons/Fwd.hpp>

namespace abyss
{
	struct SchieldEntity;
}
namespace abyss::Actor::Enemy::Schield
{
	class FaceCtrl;

	class SchieldActor :
		public EnemyActor
	{
		Ref<FaceCtrl> m_face;
	public:
		SchieldActor(const SchieldEntity& entity);

		bool accept(const ActVisitor& visitor) override;

		CShape getCollider() const;
	};
}
