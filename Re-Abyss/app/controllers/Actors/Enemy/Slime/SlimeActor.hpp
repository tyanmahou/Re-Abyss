#pragma once
#include <abyss/controllers/Actors/Enemy/EnemyActor.hpp>
#include <abyss/commons/Fwd.hpp>

#include <abyss/models/Actors/Commons/StateModel.hpp>

namespace abyss
{
	struct SlimeEntity;
}
namespace abyss::Slime
{
	class Senser;

	class SlimeActor : 
		public EnemyActor
	{
	private:
		Ref<StateModel> m_state;
	public:
		SlimeActor(const SlimeEntity& entity);

		void start()override;
		bool accept(const ActVisitor& visitor) override;

		bool isWalk()const;
    };
}