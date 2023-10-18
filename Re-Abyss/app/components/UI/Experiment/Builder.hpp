#pragma once
#if ABYSS_DEVELOP
#include <abyss/commons/Fwd.hpp>

namespace abyss::UI::Experiment
{
    struct Builder
    {
        static void Build(UIObj* pUi, const s3d::Optional<size_t>& initTopic = s3d::none);
    };
}
#endif
