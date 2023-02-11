#pragma once
#if ABYSS_DEVELOP
#include <abyss/datastores/Devs/Project/base/IProjectDataStore.hpp>
#include <Emaject.hpp>

namespace abyss::Devs::Project
{
    class GitHubDataStore : public IProjectDataStore
    {
    public:
        GitHubDataStore();
        GitHubDataStore(
            const s3d::String& owner,
            const s3d::String& repository,
            const s3d::String& token,
            const s3d::String& projectId
        );
    public:
        s3d::Array<Issue> issues() const override;
    private:
        s3d::String m_owner;
        s3d::String m_repository;
        s3d::String m_token;
        s3d::String m_projectId;
    };
    struct GitHubDataStoreInstaller : emaject::IInstaller
    {
        void onBinding(emaject::Container* container) const override;
    };
}
#endif
