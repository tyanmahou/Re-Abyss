#include "UserInfoView.hpp"

#include <abyss/commons/FontName.hpp>
#include <abyss/params/Cycle/SaveSelect/UserInfoParam.hpp>
#include <abyss/utils/DateTime/DateTimeUtil.hpp>

#include <Siv3D.hpp>

namespace abyss::Cycle::SaveSelect::UserInfo
{
    UserInfoView::UserInfoView():
        m_playerInfo(std::make_unique<ui::PlayerInfo::PlayerInfoExVM>()),
        m_player(std::make_unique<PlayerView>())
    {
    }
    void UserInfoView::draw(const User::UserModel& user) const
    {
        const auto& basePos = UserInfoParam::Common::BasePos;

        m_playerInfo
            ->setFace(U"default")
            .setOoparts(OopartsType::Nyan)
            .setHp(8)
            .setMaxHp(8)
            .setPos(basePos + UserInfoParam::HPBar::Pos)
            .draw();

        m_player->setPos(basePos + UserInfoParam::Player::Pos)
            .setTime(Scene::Time())
            .draw();
        FontAsset(FontName::UserInfo)(Name(user.getPlayMode())).draw(basePos + UserInfoParam::PlayMode::Pos);

        FontAsset(FontName::UserInfo)(U"プレイタイム").draw(basePos + UserInfoParam::PlayTime::LabelPos);
        FontAsset(FontName::UserInfo)(FormatTime(user.getPlayTime(), U"HH:mm:ss")).draw(basePos + UserInfoParam::PlayTime::Pos);

        FontAsset(FontName::UserInfo)(user.getUpdatedAt().format()).draw(basePos + UserInfoParam::UpdatedAt::Pos);
    }
}
