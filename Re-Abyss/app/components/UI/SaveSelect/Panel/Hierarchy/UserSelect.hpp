#pragma once
#include <abyss/components/UI/Common/HierarchyCtrl.hpp>
#include <abyss/models/User/UserModel.hpp>
#include <abyss/views/UI/SaveSelect/BackGround/BackGroundVM.hpp>
#include <abyss/views/UI/SaveSelect/SelectFrame/SelectFrameVM.hpp>
#include <abyss/views/UI/SaveSelect/UserInfo/UserInfoView.hpp>
#include <Siv3D/HashTable.hpp>

namespace abyss::UI::SaveSelect::Panel
{
    class UserSelect : public IHierarchy
    {
        enum class Mode
        {
            GameStart,
            Delete,
        };
    public:
        UserSelect(UIObj* pUi);

        void start() override;

        bool update() override;

        void draw() const override;

        private:
            UIObj* m_pUi;
            s3d::int32 m_selectId = 0;
            Mode m_mode = Mode::GameStart;
            s3d::HashTable<s3d::int32, User::UserModel> m_users;

            std::unique_ptr<BackGround::BackGroundVM> m_bg;
            std::unique_ptr<SelectFrame::SelectFrameVM> m_selectFrame;
            std::unique_ptr<UserInfo::UserInfoView> m_userInfo;
    };
}