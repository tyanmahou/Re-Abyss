#include "DBDataStore.hpp"
#include <abyss/commons/Resource/UserData/Manager/Manager.hpp>

namespace abyss
{
    DBDataStore::DBDataStore():
        m_db(Resource::SaveUtil::DB())
    {}

    DBDataStore::DBDataStore(const s3d::String& path) :
        m_db(Resource::UserData::Manager::LoadDB(path))
    {}

    DBDataStore::DBDataStore(const std::shared_ptr<s3dsql::SQLite3>& db) :
        m_db(*db)
    {}

    DBInstaller::DBInstaller() :
        m_db(std::make_shared<s3dsql::SQLite3>(Resource::SaveUtil::DB()))
    {}

    DBInstaller::DBInstaller(const s3d::String& path):
        m_db(std::make_shared<s3dsql::SQLite3>(Resource::UserData::Manager::LoadDB(path)))
    {}

    void DBInstaller::onBinding(emaject::Container * conatienr) const
    {
        conatienr->bind<s3dsql::SQLite3>()
            .fromInstance(m_db)
            .asCache();
    }

}
