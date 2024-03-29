#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/models/User/UserModel.hpp>
#include <Siv3D/HashTable.hpp>

namespace abyss::UI::SaveSelect::Main
{
    class Users : public IComponent
    {
    public:
        Users(UIObj* pUi);

        s3d::Optional<User::UserModel> getUser(s3d::int32 userId) const;

        bool isContains(s3d::int32 userId) const;

        /// <summary>
        /// ログイン
        /// </summary>
        void login(s3d::int32 userId);

        /// <summary>
        /// 作成
        /// </summary>
        void create(s3d::int32 userId, UserPlayMode playMode);

        /// <summary>
        /// 削除
        /// </summary>
        void erase(s3d::int32 userId);
    private:
        UIObj* m_pUi;
        s3d::HashTable<s3d::int32, User::UserModel> m_users;
        s3d::int32 m_selectId = 0;
    };
}