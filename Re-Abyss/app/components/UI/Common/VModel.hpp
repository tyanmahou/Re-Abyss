#pragma once
#include <abyss/components/Common/VModelBase.hpp>
#include <abyss/modules/UI/base/IDraw.hpp>

namespace abyss::UI
{
    /// <summary>
    /// ViewModel Bind
    /// </summary>
    using VModel = VModelBase<IDraw>;
}