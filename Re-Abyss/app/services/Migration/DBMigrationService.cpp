#include <abyss/services/Migration/DBMigrationService.hpp>

#include <abyss/datastores/Migration/base/IMigrationDataStore.hpp>
#include <abyss/datastores/MigrationVersion/base/IMigrationVersionDataStore.hpp>

namespace abyss::User
{
    void DBMigrationService::up() const
    {
        // DBなければ生成
        m_version->create();

        // 現在のバージョン取得
        auto current = m_version->selectCurrentVersion();

        // 最新までアップデート
        s3d::Array<s3d::int64> updateVersions = m_migrarion->updateVersionIds(current);
        if (updateVersions.empty()) {
            // 更新無し
            return;
        }
        for (auto version : updateVersions) {
            m_migrarion->up(version);
        }
        m_version->update(updateVersions);
    }
    void DBMigrationService::down() const
    {
        auto current = m_version->selectCurrentVersion();
        if (current <= 0) {
            return;
        }
        m_version->erase(current);
        m_migrarion->down(current);
    }
    void DBMigrationServiceInstaller::onBinding(emaject::Container* container) const
    {
        container->bind<IMigrationService>()
            .to<DBMigrationService>()
            .asCache();
    }
}
