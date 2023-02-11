#pragma once
#if ABYSS_DEVELOP
#include <abyss/services/Devs/Project/base/IProjectService.hpp>
#include <abyss/modules/Devs/Project/base/Tasks.hpp>
#include <Emaject.hpp>

namespace abyss::Devs::Project
{
    class IProjectDataStore;

    class ProjectService : public IProjectService
    {
    public:
        INJECT_CTOR(ProjectService(
            std::shared_ptr<IProjectDataStore> datastore
        ));

        const s3d::Array<Issue>& issues(TaskStatus status) const override;
    private:
        Tasks m_tasks;
    };

    struct ProjectServiceInstaller : emaject::IInstaller
    {
        void onBinding(emaject::Container* container) const override;
    };
}
#endif
