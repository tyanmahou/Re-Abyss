#pragma once

#include <abyss/models/User/UserModel.hpp>
#include <abyss/views/Cycle/SaveSelect/UserInfo/PlayerView.hpp>
#include <abyss/views/Cycle/SaveSelect/UserInfo/OopartsListView.hpp>
#include <abyss/views/UI/PlayerInfo/PlayerInfoExVM.hpp>

namespace abyss::Cycle::SaveSelect::UserInfo
{
    /// <summary>
    /// ユーザー情報
    /// </summary>
    class UserInfoView
    {
        std::unique_ptr<UI::PlayerInfo::PlayerInfoExVM> m_playerInfo;
        std::unique_ptr<PlayerView> m_player;
        std::unique_ptr<OopartsListView> m_oopartsList;

    public:
        UserInfoView();

        void draw(const User::UserModel& user) const;
    };
}