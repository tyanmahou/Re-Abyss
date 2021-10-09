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

    bool Users::isValidUser() const
    {
        return m_selectId != -1 && m_users.contains(m_selectId);
    }
    s3d::Optional<User::UserModel> Users::getSelectUser() const
    {
        if (this->isValidUser()) {
            return m_users.at(m_selectId);
        }
        return s3d::none;
    }
}
