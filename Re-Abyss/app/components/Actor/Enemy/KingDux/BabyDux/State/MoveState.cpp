#include <abyss/components/Actor/Enemy/KingDux/BabyDux/State/MoveState.hpp>
#include <Siv3D.hpp>

namespace abyss::Actor::Enemy::KingDux::BabyDux
{
	void MoveState::start()
	{

	}
	Task<> MoveState::task()
	{
		co_return;
	}
}