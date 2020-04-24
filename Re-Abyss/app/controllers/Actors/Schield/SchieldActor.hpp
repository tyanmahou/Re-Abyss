#pragma once
#include <abyss/controllers/Actors/Enemy/EnemyActor.hpp>
#include <abyss/commons/Fwd.hpp>
#include <abyss/controllers/Actors/base/IState.hpp>

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
		StateManager<SchieldActor> m_state;
		std::shared_ptr<SchieldVM> m_view;
	public:
		SchieldActor(const SchieldEntity& entity);

		void update(double)override;
		void draw()const;
		s3d::Circle getFaceCollider() const;
		CShape getCollider()const override;
		void onCollisionStay(ICollider* col) override;
		bool accept(const ActVisitor& visitor) override;

		SchieldVM* getBindedView()const;
	};
}
