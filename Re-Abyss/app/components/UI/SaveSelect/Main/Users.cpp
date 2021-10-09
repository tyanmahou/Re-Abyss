#include "Users.hpp"
#include <abyss/commons/Resource/UserData/Storage/Storage.hpp>
#include <abyss/commons/Resource/SaveUtil.hpp>
#include <abyss/services/User/base/IUserService.hpp>

namespace abyss::UI::SaveSelect::Main
{
    using Resource::UserData::Storage;

    Users::Users():
        m_users(Storage::Get<User::IUserService>()->getUsers())
    {}
}
