#pragma once
#include <memory>
#include <abyss/services/Migration/base/IMigrationService.hpp>
#include <Emaject.hpp>

namespace abyss::User
{
    class IMigrationDataStore;
    class IMigrationVersionDataStore;

    class DBMigrationService : public IMigrationService
    {
    public:
        void up() const override;
        void down() const override;
    private:
        [[INJECT(m_migrarion)]]
        std::shared_ptr<IMigrationDataStore> m_migrarion;
        [[INJECT(m_version)]]
        std::shared_ptr<IMigrationVersionDataStore> m_version;
    };

    struct DBMigrationServiceInstaller : emaject::IInstaller
    {
        void onBinding(emaject::Container* container) const override;
    };
}