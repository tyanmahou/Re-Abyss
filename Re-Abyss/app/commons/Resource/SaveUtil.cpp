#include "SaveUtil.hpp"
#include <abyss/commons/Resource/UserData/Manager/Manager.hpp>
#include <abyss/commons/Resource/UserData/Storage/Storage.hpp>

#include <abyss/services/User/base/IUserService.hpp>

#include <abyss/models/User/UserModel.hpp>
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
    UserModel CreateUser(s3d::int32 userId)
    {
        return Storage::Get<IUserService>()->create(userId);
    }

    UserModel Login(const UserModel& user)
    {
        return Storage::Get<IUserService>()->login(user);
    }
}
