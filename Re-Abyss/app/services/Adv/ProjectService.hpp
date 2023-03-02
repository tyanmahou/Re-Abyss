#pragma once
#include <abyss/services/Adv/base/IProjectService.hpp>
#include <Emaject.hpp>

namespace abyss::Adv
{
    class IProjectDataStore;

    class ProjectService final : public IProjectService
    {
    public:
        INJECT_CTOR(ProjectService(
            std::shared_ptr<IProjectDataStore> datastore
        ));

        const s3d::Array<Chara>& getCharas() const override
        {
            return m_charas;
        }
    private:
        s3d::Array<Chara> m_charas;
    };

    struct ProjectServiceInstaller : emaject::IInstaller
    {
        void onBinding(emaject::Container* container) const override;
    };
}
