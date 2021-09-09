#include "HandRecipe.hpp"
#include <Siv3D.hpp>
#include <abyss/params/Actor/Enemy/CodeZero/HandParam.hpp>

namespace abyss::Actor::Enemy::CodeZero::Hand
{
    HandRecipe HandRecipe::CreateLeftPhase1()
    {
        return HandRecipe{
            .axis = Axis2::FromRight(s3d::Vec2{-1, 0 }),
            .distance = HandParam::Base::HorizontalDist,
            .rotateLimit = Math::ToRadians(40)
        };
    }
    HandRecipe HandRecipe::CreateRightPhase1()
    {
        return HandRecipe{
            .axis = Axis2::FromRight(s3d::Vec2{0, 1 }),
            .distance = HandParam::Base::VerticalDist,
            .rotateLimit = Math::ToRadians(50)
        };
    }
    HandRecipe HandRecipe::CreateLeftPhase2()
    {
        return HandRecipe{
            .axis = Axis2::FromRight(s3d::Vec2{0, 1 }),
            .distance = HandParam::Base::VerticalDist,
            .rotateLimit = Math::ToRadians(-50)
        };
    }
    HandRecipe HandRecipe::CreateRightPhase2()
    {
        return HandRecipe{
            .axis = Axis2::FromRight(s3d::Vec2{1, 0 }),
            .distance = HandParam::Base::HorizontalDist,
            .rotateLimit = Math::ToRadians(-40)
        };
    }
}
