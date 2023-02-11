#pragma once
#if ABYSS_DEVELOP
#include <abyss/modules/Devs/Project/base/Issue.hpp>

namespace abyss::Devs::Project
{
    class IProjectService
    {
    public:
        virtual ~IProjectService() = default;

        virtual const s3d::Array<Issue>& issues(TaskStatus status) const = 0;
    };
}
#endif
