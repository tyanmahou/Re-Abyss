#include "SaveUtil.hpp"
#include "UserData/Manager/Manager.hpp"

namespace abyss::Resource::SaveUtil
{
    s3dsql::SQLite3 DB()
    {
        return UserData::Manager::LoadDB(U"savedata");
    }
}
