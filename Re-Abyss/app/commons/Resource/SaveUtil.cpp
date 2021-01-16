#include "SaveUtil.hpp"
#include <abyss/commons/Resource/UserData/Manager/Manager.hpp>
#include <abyss/commons/Resource/UserData/Storage/Storage.hpp>
#include <abyss/services/User/base/IUserService.hpp>

namespace abyss::Resource::SaveUtil
{
    using namespace abyss::User;
    using namespace abyss::Resource::UserData;

    s3dsql::SQLite3 DB()
    {
        return UserData::Manager::LoadDB(U"savedata");
    }
    bool EraseUser(s3d::int32 userId)
    {
        Storage::Get<IUserService>()->erase(userId);
        return true;
    }
}
