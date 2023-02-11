#pragma once
#if ABYSS_DEVELOP
#include <abyss/modules/Devs/Project/base/Issue.hpp>
namespace abyss::Devs::Project
{
    class IProjectDataStore
    {
    public:
        virtual ~IProjectDataStore() = default;

        virtual s3d::Array<Issue> issues() const = 0;
    };
}
#endif
