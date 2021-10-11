#include "Users.hpp"
#include <abyss/commons/Resource/UserData/Storage/Storage.hpp>
#include <abyss/commons/Resource/SaveUtil.hpp>
#include <abyss/services/User/base/IUserService.hpp>

namespace abyss::UI::SaveSelect::Main
{
    using Resource::UserData::Storage;

    Users::Users(UIObj* pUi):
        m_pUi(pUi),
        m_users(Storage::Get<User::IUserService>()->getUsers())
    {}

    bool Users::isContains(s3d::int32 userId) const
    {
        return m_users.contains(userId);
    }
    s3d::Optional<User::UserModel> Users::getUser(s3d::int32 userId) const
    {
        if (this->isContains(userId)) {
            return m_users.at(userId);
        }
        return s3d::none;
    }
    void Users::login(s3d::int32 userId)
    {
        m_users[userId] = Resource::SaveUtil::Login(m_users[userId]);
    }
    void Users::create(s3d::int32 userId, UserPlayMode playMode)
    {
        m_users[userId] = Resource::SaveUtil::CreateUser(userId, playMode);
    }

    void Users::erase(s3d::int32 userId)
    {
        Resource::SaveUtil::EraseUser(userId);
        m_users.erase(userId);
    }
}
