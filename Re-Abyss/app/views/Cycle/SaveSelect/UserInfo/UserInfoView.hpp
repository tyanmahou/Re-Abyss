#pragma once

#include <abyss/models/User/UserModel.hpp>
#include <abyss/views/UI/PlayerInfo/PlayerInfoExVM.hpp>

namespace abyss::Cycle::SaveSelect::UserInfo
{
    /// <summary>
    /// ユーザー情報
    /// </summary>
    class UserInfoView
    {
        std::unique_ptr<ui::PlayerInfo::PlayerInfoExVM> m_playerInfo;

    public:
        UserInfoView();

        void draw(const User::UserModel& user) const;
    };
}