#pragma once
#include <abyss/components/Common/CustomDrawBase.hpp>
#include <abyss/modules/Actor/base/IDraw.hpp>

namespace abyss::Actor
{
    /// <summary>
    /// 汎用描画
    /// </summary>
    using CustomDraw = CustomDrawBase<IDraw>;
}