#pragma once
#include <abyss/views/Actors/Ooparts/base/BaseVM.hpp>
#include <abyss/types/OopartsType.hpp>

namespace abyss::Actor::Ooparts::OopartsViewUtil
{
    /// <summary>
    /// タイプからView生成
    /// </summary>
    std::shared_ptr<BaseVM> CreateViewFromType(OopartsType type);
}