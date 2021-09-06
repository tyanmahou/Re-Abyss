#pragma once
#include <abyss/components/Common/CustomDrawBase.hpp>
#include <abyss/components/Decor/base/IDraw.hpp>

namespace abyss::Decor
{
    /// <summary>
    /// 汎用描画
    /// </summary>
    using CustomDraw = CustomDrawBase<IDraw>;
}