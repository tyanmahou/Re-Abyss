#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/UI/SaveSelect/Main/Users.hpp>
#include <abyss/utils/Ref/Ref.hpp>
#include <Siv3D/Optional.hpp>

namespace abyss::UI::SaveSelect::Main
{
    class UserSelector : public IComponent
    {
    public:
        UserSelector(UIObj* pUi);

        void onStart() override;

        /// <summary>
        /// 選択の更新
        /// </summary>
        /// <returns>最新の選択中</returns>
        s3d::int32 onUpdate();

        void setSelectId(s3d::int32 id)
        {
            m_selectId = id;
        }
        s3d::int32 getSelectId() const
        {
            return m_selectId;
        }

        /// <summary>
        /// 有効なユーザーか
        /// </summary>
        /// <returns></returns>
        bool isValidUser() const;

        /// <summary>
        /// 削除選択中
        /// </summary>
        bool isDeleteSelect() const;

        /// <summary>
        /// 選択中のユーザーを取得
        /// </summary>
        /// <returns></returns>
        s3d::Optional<User::UserModel> getSelectUser() const;
    private:
        UIObj* m_pUi;
        Ref<Users> m_users;
        s3d::int32 m_selectId = 0;
    };
}