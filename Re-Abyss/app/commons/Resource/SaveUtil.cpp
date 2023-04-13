#include <abyss/commons/Resource/SaveUtil.hpp>
#include <abyss/commons/Resource/UserData/Manager/Manager.hpp>

namespace abyss::Resource::SaveUtil
{
    s3dsql::SQLite3 DB()
    {
        return UserData::Manager::LoadDB(U"savedata");
    }
}
