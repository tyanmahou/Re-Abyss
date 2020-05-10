#pragma once
#include <abyss/controllers/Actors/Enemy/EnemyActor.hpp>
#include <abyss/commons/Fwd.hpp>

#include <abyss/models/Actors/base/StateModel.hpp>

namespace abyss
{
	struct SlimeEntity;
}
namespace abyss::Slime
{
	class Senser;
	class SlimeVM;

	class SlimeActor : 
		public EnemyActor
	{
	public:
		enum State
		{
			Walk,
			Jump
		};
	private:
		Ref<exp::StateModel<SlimeActor>> m_state;
		std::shared_ptr<SlimeVM> m_view;
	public:
		SlimeActor(const SlimeEntity& entity);

		void start()override;
		bool accept(const ActVisitor& visitor) override;

		SlimeVM* getBindedView()const;

		bool isWalk()const;
    };
}