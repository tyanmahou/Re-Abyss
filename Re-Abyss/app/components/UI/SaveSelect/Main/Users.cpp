#include <abyss/components/UI/SaveSelect/Main/Users.hpp>
#include <abyss/modules/UI/base/UIObj.hpp>
#include <abyss/modules/User/Storage.hpp>

namespace abyss::UI::SaveSelect::Main
{
    Users::Users(UIObj* pUi):
        m_pUi(pUi),
        m_users(pUi->getModule<Storage>()->getUsers())
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
        m_users[userId] = m_pUi->getModule<Storage>()->login(m_users[userId]);
    }
    void Users::create(s3d::int32 userId, UserPlayMode playMode)
    {
        m_users[userId] = m_pUi->getModule<Storage>()->createUser(userId, playMode);
    }

    void Users::erase(s3d::int32 userId)
    {
        m_pUi->getModule<Storage>()->eraseUser(userId);
        m_users.erase(userId);
    }
}
