#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/models/User/UserModel.hpp>
#include <Siv3D/HashTable.hpp>

namespace abyss::UI::SaveSelect::Main
{
    class Users : public IComponent
    {
    public:
        Users(UIObj* pUi);

        void setSelectId(s3d::int32 id)
        {
            m_selectId = id;
        }
        s3d::int32 getSelectId() const
        {
            return m_selectId;
        }

        bool isValidUser() const;

        s3d::Optional<User::UserModel> getSelectUser() const;
    private:
        UIObj* m_pUi;
        s3d::HashTable<s3d::int32, User::UserModel> m_users;
        s3d::int32 m_selectId = 0;
    };
}