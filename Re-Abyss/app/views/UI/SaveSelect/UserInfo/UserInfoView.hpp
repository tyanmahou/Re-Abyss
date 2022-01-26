#pragma once
#include <abyss/models/User/UserModel.hpp>
#include <abyss/views/UI/SaveSelect/UserInfo/PlayerView.hpp>
#include <abyss/views/UI/SaveSelect/UserInfo/OopartsListView.hpp>
#include <abyss/views/UI/PlayerInfo/PlayerInfoExVM.hpp>

namespace abyss::UI::SaveSelect::UserInfo
{
    /// <summary>
    /// ユーザー情報
    /// </summary>
    class UserInfoView
    {
        std::unique_ptr<UI::PlayerInfo::PlayerInfoExVM> m_playerInfo;
        std::unique_ptr<PlayerView> m_player;
        std::unique_ptr<OopartsListView> m_oopartsList;
        double m_time = 0;
    public:
        UserInfoView();

        PlayerView* getPlayerView() const
        {
            return m_player.get();
        }
        UserInfoView& setTime(double time)
        {
            m_time = time;
            return *this;
        }
        void draw(const User::UserModel& user) const;
    };
}