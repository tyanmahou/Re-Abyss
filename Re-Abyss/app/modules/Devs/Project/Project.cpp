#if ABYSS_DEVELOP
#include <abyss/modules/Devs/Project/Project.hpp>
#include <abyss/services/Devs/Project/base/IProjectService.hpp>

namespace abyss::Devs::Project
{
    Project::Project(std::shared_ptr<IProjectService> service):
        m_service(service)
    {
    }

    const s3d::Array<Issue>& Project::issues(TaskStatus status) const
    {
        return m_service->issues(status);
    }

    bool Project::open(const s3d::URL& url) const
    {
        return System::LaunchBrowser(url);
    }

}
#endif
