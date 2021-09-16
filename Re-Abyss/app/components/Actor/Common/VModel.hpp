#pragma once
#include <abyss/components/Common/VModelBase.hpp>
#include <abyss/components/Actor/base/IDraw.hpp>

namespace abyss::Actor
{
    /// <summary>
    /// ViewModel Bind
    /// </summary>
    using VModel = VModelBase<IDraw>;

    template<s3d::uint16 Slot> requires (Slot > 0)
    using VModelSub = VModelBase<IDraw, Slot>;
}