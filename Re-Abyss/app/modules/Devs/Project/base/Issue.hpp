#pragma once
#if ABYSS_DEVELOP
#include <abyss/modules/Devs/Project/base/TaskStatus.hpp>
#include <Siv3D/String.hpp>

namespace abyss::Devs::Project
{
    /// <summary>
    /// イシュー
    /// </summary>
    struct Issue
    {
        s3d::String title;

        s3d::URL url;

        TaskStatus status;
    };
}
#endif
