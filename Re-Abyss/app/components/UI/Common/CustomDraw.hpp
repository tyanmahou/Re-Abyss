#pragma once
#include <abyss/components/Common/CustomDrawBase.hpp>
#include <abyss/modules/UI/base/IDraw.hpp>

namespace abyss::UI
{
    /// <summary>
    /// 汎用描画
    /// </summary>
    using CustomDraw = CustomDrawBase<IDraw>;
}