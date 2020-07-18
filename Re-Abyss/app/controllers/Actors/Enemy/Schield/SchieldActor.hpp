#pragma once
#include <abyss/controllers/Actors/Enemy/EnemyActor.hpp>
#include <abyss/commons/Fwd.hpp>

namespace abyss
{
	struct SchieldEntity;
}
namespace abyss::Schield
{
	class FaceCtrlModel;

	class SchieldActor :
		public EnemyActor
	{
		Ref<FaceCtrlModel> m_face;
	public:
		SchieldActor(const SchieldEntity& entity);

		bool accept(const ActVisitor& visitor) override;

		CShape getCollider() const;
	};
}
