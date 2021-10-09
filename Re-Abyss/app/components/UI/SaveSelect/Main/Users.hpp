#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/models/User/UserModel.hpp>
#include <Siv3D/HashTable.hpp>

namespace abyss::UI::SaveSelect::Main
{
    class Users : public IComponent
    {
    public:
        Users();

    private:
        s3d::HashTable<s3d::int32, User::UserModel> m_users;
    };
}