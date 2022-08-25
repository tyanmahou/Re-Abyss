#pragma once
#include <abyss/views/Actor/Ooparts/base/BaseVM.hpp>
#include <abyss/entities/OopartsType.hpp>

namespace abyss::Actor::Ooparts::OopartsViewUtil
{
    /// <summary>
    /// タイプからView生成
    /// </summary>
    std::shared_ptr<BaseVM> CreateViewFromType(OopartsType type);
}
