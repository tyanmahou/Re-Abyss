#include "HandParam.hpp"
#include <Siv3D.hpp>

namespace abyss::Actor::Enemy::CodeZero::Hand
{
    HandParam HandParam::CreateLeftPhase1()
    {
        return HandParam{
            .axis = Axis2::FromRight(s3d::Vec2{-1, 0 }),
            .distance = 400,
            .rotateLimit = Math::ToRadians(40)
        };
    }
    HandParam HandParam::CreateRightPhase1()
    {
        return HandParam{
            .axis = Axis2::FromRight(s3d::Vec2{0, 1 }),
            .distance = 250,
            .rotateLimit = Math::ToRadians(50)
        };
    }
    HandParam HandParam::CreateLeftPhase2()
    {
        return HandParam{
            .axis = Axis2::FromRight(s3d::Vec2{0, 1 }),
            .distance = 250,
            .rotateLimit = Math::ToRadians(-50)
        };
    }
    HandParam HandParam::CreateRightPhase2()
    {
        return HandParam{
            .axis = Axis2::FromRight(s3d::Vec2{1, 0 }),
            .distance = 400,
            .rotateLimit = Math::ToRadians(-40)
        };
    }
}
