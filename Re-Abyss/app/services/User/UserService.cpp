#include "UserService.hpp"
#include <abyss/models/User/UserModel.hpp>
#include <abyss/datastores/User/base/IUserDataStore.hpp>

#include <Siv3D.hpp>

namespace abyss::User
{
    s3d::HashTable<s3d::int32, UserModel> UserService::getUsers() const
    {
        s3d::HashTable<s3d::int32, UserModel> ret;

        for (auto&& entity : m_users->selectAll()) {
            ret[entity.userId] = UserModel()
                .setUserId(entity.userId)
                .setPlayMode(entity.playMode)
                .setPlayTime(entity.playTime)
                .setUpdatedAt(entity.updatedAt)
                .setCreatedAt(entity.createdAt)
                ;
        }
        return ret;
    }

    UserModel UserService::create(s3d::int32 userId, UserPlayMode playMode) const
    {
        auto now = s3d::DateTime::Now();
        UserModel newUser;
        newUser
            .setUserId(userId)
            .setPlayMode(playMode)
            .setPlayTime(0s)
            .setUpdatedAt(now)
            .setCreatedAt(now)
            ;

        m_users->update(UserEntity{
            .userId = userId,
            .playMode = playMode,
            .playTime = 0s,
        });
        return newUser;
    }

    UserModel UserService::login(const UserModel& user) const
    {
        m_users->update(UserEntity{
            .userId = user.getUserId(),
            .playMode = user.getPlayMode(),
            .playTime = user.getPlayTime(),
            });
        UserModel updated = user;
        updated.setUpdatedAt(DateTime::Now());
        return updated;
    }

    bool UserService::erase(s3d::int32 userId) const
    {
        return m_users->erase(userId);
    }

    void UserServiceInstaller::onBinding(emaject::Container* container) const
    {
        container->bind<IUserService>()
            .to<UserService>()
            .asSingle();
    }

}
