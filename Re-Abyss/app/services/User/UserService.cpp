#include "UserService.hpp"
#include <abyss/models/User/UserModel.hpp>
#include <abyss/datastores/User/base/IUserDataStore.hpp>

namespace abyss::User
{
    s3d::Array<UserModel> UserService::getUsers() const
    {
        s3d::Array<UserModel> ret;
        return ret;
    }

    UserModel UserService::create(s3d::int32 userId, UserPlayMode playMode) const
    {
        return UserModel();
    }

    void UserServiceInstaller::onBinding(emaject::Container* container) const
    {
        container->bind<IUserService>()
            .to<UserService>()
            .asSingle();
    }

}
