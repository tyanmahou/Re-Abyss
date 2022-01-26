#include <abyss/commons/Resource/UserData/Migration/Migration.hpp>

#include <abyss/commons/Resource/SaveUtil.hpp>
#include <abyss/services/Migration/base/IMigrationService.hpp>
#include <abyss/factories/Migration/MigrationInjector.hpp>
#include <abyss/debugs/Log/Log.hpp>

#include <Siv3D.hpp>
#include <Siv3D/EngineLog.hpp>
#include <Siv3DSQL.hpp>

namespace abyss::Resource::UserData
{
    class Migration::Impl
    {
    public:
        Impl()
        {
            m_migration = Factory::Migration::Injector().resolve<User::IMigrationService>();
        }
        bool update()
        {
            auto&& db = SaveUtil::DB();
            try {
                // トランザクション開始
                auto transaction = db.beginTransaction();
                m_migration->up();
                transaction.commit();
            } catch (s3dsql::SQLError& error) {
                LOG_ERROR(error.what());
#if ABYSS_DEBUG
                Debug::LogError << error;
#endif
                return false;
            }
            return true;
        }
    private:
        std::shared_ptr<User::IMigrationService> m_migration;
    };
    bool Migration::Update()
    {
        return Instance()->m_pImpl->update();
    }
    Migration::Migration():
        m_pImpl(std::make_unique<Impl>())
    {}

}
