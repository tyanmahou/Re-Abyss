#include <abyss/views/UI/SaveSelect/UserInfo/UserInfoView.hpp>

#include <abyss/commons/FontName.hpp>
#include <abyss/commons/MsgUtil.hpp>
#include <abyss/params/UI/SaveSelect/Param.hpp>
#include <abyss/params/UI/SaveSelect/UserInfoParam.hpp>
#include <abyss/utils/DateTime/DateTimeUtil.hpp>
#include <abyss/views/util/Anchor/AnchorUtil.hpp>
#include <Siv3D.hpp>

namespace abyss::UI::SaveSelect::UserInfo
{
    UserInfoView::UserInfoView():
        m_playerInfo(std::make_unique<UI::PlayerInfo::PlayerInfoExVM>()),
        m_player(std::make_unique<PlayerView>()),
        m_oopartsList(std::make_unique<OopartsListView>())
    {
    }
    void UserInfoView::draw(const User::UserModel& user) const
    {
        const Vec2 basePos = AnchorUtil::FromCc(Param::SelectFrame::BasePos) + UserInfoParam::Common::BasePos;

        m_playerInfo
            ->setFace(U"default")
            .setOoparts(OopartsType::Nyan)
            .setHp(8)
            .setMaxHp(8)
            .setPos(basePos + UserInfoParam::HPBar::Pos)
            .draw();

        // Chapter
        {
            FontAsset(FontName::Chapter)(U"Chapter").draw(basePos + UserInfoParam::Chapter::LabelPos);
            FontAsset(FontName::UserInfo)(U"あいうえお").drawAt(basePos + UserInfoParam::Chapter::PosAt);

            Line(basePos + UserInfoParam::Chapter::LinePos, Arg::direction = Vec2::UnitX() * UserInfoParam::Chapter::LineLength).draw(1.0);
        }
        m_player
            ->setPos(basePos + UserInfoParam::Player::Pos)
            .setOoparts(OopartsType::Nyan)
            .setTime(m_time)
            .draw();
        FontAsset(FontName::UserInfo)(MsgUtil::Name(user.getPlayMode())).draw(basePos + UserInfoParam::PlayMode::Pos);

        FontAsset(FontName::UserInfo)(U"プレイタイム").draw(basePos + UserInfoParam::PlayTime::LabelPos);
        FontAsset(FontName::UserInfo)(FormatTime(user.getPlayTime(), U"HH:mm:ss")).draw(basePos + UserInfoParam::PlayTime::Pos);

        FontAsset(FontName::UserInfo)(user.getUpdatedAt().format(DateTimeUtil::FormatFromDateTime)).draw(basePos + UserInfoParam::UpdatedAt::Pos);

        m_oopartsList
            ->setPos(basePos + UserInfoParam::OopartsList::Pos)
            .setOffsetX(UserInfoParam::OopartsList::OffsetX)
            // TODO
            .setHaving({OopartsType::Xto, OopartsType::Nyan})
            .draw();
    }
}
