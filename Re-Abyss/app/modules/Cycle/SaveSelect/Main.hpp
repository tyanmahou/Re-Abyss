#pragma once
#include <memory>

#include <abyss/models/User/UserModel.hpp>

#include <Siv3D/Fwd.hpp>
#include <Siv3D/HashTable.hpp>

namespace abyss::Cycle::SaveSelect
{
    namespace BackGround
    {
        class BackGroundVM;
    }
    namespace SelectFrame
    {
        class SelectFrameVM;
    }
    namespace UserInfo
    {
        class UserInfoView;
    }

    class IMainObserver
    {
    public:
        virtual ~IMainObserver() = default;

        virtual void onNewGame() = 0;
        virtual void onLoadGame() = 0;
        virtual void onBack() = 0;
    };
    class Main
    {
        IMainObserver* m_observer;

        enum class Mode
        {
            GameStart,
            Delete,
        };
        s3d::int32 m_selectId = 0;
        Mode m_mode = Mode::GameStart;

        s3d::HashTable<s3d::int32, User::UserModel> m_users;

        std::unique_ptr<BackGround::BackGroundVM> m_bg;
        std::unique_ptr<SelectFrame::SelectFrameVM> m_selectFrame;
        std::unique_ptr<UserInfo::UserInfoView> m_userInfo;
    public:
        Main(IMainObserver* observer);
        ~Main();

        void update();

        void draw()const;

        void finally();
    };
}