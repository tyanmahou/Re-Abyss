#include "HandDesc.hpp"
#include <Siv3D.hpp>
#include <abyss/params/Actor/Enemy/CodeZero/HandParam.hpp>

namespace abyss::Actor::Enemy::CodeZero::Hand
{
    HandDesc HandDesc::CreateLeftPhase1()
    {
        return HandDesc{
            .axis = Axis2::FromRight(s3d::Vec2{-1, 0 }),
            .distance = HandParam::Base::HorizontalDist,
            .rotateLimit = Math::ToRadians(40)
        };
    }
    HandDesc HandDesc::CreateRightPhase1()
    {
        return HandDesc{
            .axis = Axis2::FromRight(s3d::Vec2{0, 1 }),
            .distance = HandParam::Base::VerticalDist,
            .rotateLimit = Math::ToRadians(50)
        };
    }
    HandDesc HandDesc::CreateLeftPhase2()
    {
        return HandDesc{
            .axis = Axis2::FromRight(s3d::Vec2{0, 1 }),
            .distance = HandParam::Base::VerticalDist,
            .rotateLimit = Math::ToRadians(-50)
        };
    }
    HandDesc HandDesc::CreateRightPhase2()
    {
        return HandDesc{
            .axis = Axis2::FromRight(s3d::Vec2{1, 0 }),
            .distance = HandParam::Base::HorizontalDist,
            .rotateLimit = Math::ToRadians(-40)
        };
    }
}
