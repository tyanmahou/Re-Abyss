#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/components/UI/base/IUpdate.hpp>
#include <abyss/components/UI/SaveSelect/Main/ModeCtrl.hpp>
#include <abyss/components/UI/SaveSelect/Main/Users.hpp>
#include <abyss/utils/Ref/Ref.hpp>
#include <abyss/utils/Coro/TaskHolder/TaskHolder.hpp>
#include <Siv3D/Optional.hpp>

namespace abyss::UI::SaveSelect::Main
{
    class UserSelector : 
        public IComponent,
        public IUpdate
    {
    public:
        UserSelector(UIObj* pUi);

        void setup(Executer executer)  override;
        void onStart() override;

        void onUpdate() override;

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
        Coro::Task<> stateSelect();
        Coro::Task<> stateCreateUserConfirm();
        Coro::Task<> stateEraseUserConfirm();
    private:
        UIObj* m_pUi;
        Ref<ModeCtrl> m_mode;
        Ref<Users> m_users;
        s3d::int32 m_selectId = 0;

        Coro::TaskHolder<> m_state;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<UI::SaveSelect::Main::UserSelector>
    {
        using Base = MultiComponents<
            UI::IUpdate
        >;
    };
}