#include <abyss/components/Actor/Player/PlayerDesc.hpp>
#include <abyss/params/Actor/Player/Param.hpp>

namespace abyss::Actor::Player
{
    PlayerDesc::PlayerDesc():
        hp(Param::Base::Hp),
        startId(0)
    {
    }
}
