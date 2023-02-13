#if ABYSS_DEVELOP
#include <abyss/services/Devs/Project/ProjectService.hpp>
#include <abyss/datastores/Devs/Project/base/IProjectDataStore.hpp>

namespace abyss::Devs::Project
{
    ProjectService::ProjectService(std::shared_ptr<IProjectDataStore>datastore)
    {
        for (auto&& issue : datastore->issues()) {
            m_tasks.add(std::move(issue));
        }
    }
    const s3d::Array<Issue>& ProjectService::issues(TaskStatus status) const
    {
        return m_tasks.issues(status);
    }
    void ProjectServiceInstaller::onBinding(emaject::Container* container) const
    {
        container->bind<IProjectService>()
            .to<ProjectService>()
            .asCached();
    }
}
#endif
