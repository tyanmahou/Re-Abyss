#pragma once
#include <abyss/controllers/Actors/Enemy/EnemyActor.hpp>
#include <abyss/commons/Fwd.hpp>
#include <abyss/models/Actors/base/StateModel.hpp>

namespace abyss
{
	struct SchieldEntity;
}
namespace abyss::Schield
{
	class SchieldVM;

	class SchieldActor :
		public EnemyActor
	{
	public:
		enum State
		{
			Wait,
			AttackPlus,
			AttackCross,
		};
	private:
		Ref<exp::StateModel<SchieldActor>> m_state;
		std::shared_ptr<SchieldVM> m_view;
	public:
		SchieldActor(const SchieldEntity& entity);

		s3d::Circle getFaceCollider() const;
		CShape getCollider()const override;
		bool accept(const ActVisitor& visitor) override;

		SchieldVM* getBindedView()const;
	};
}
