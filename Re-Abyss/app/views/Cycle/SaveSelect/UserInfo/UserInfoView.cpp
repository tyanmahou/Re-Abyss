#include "UserInfoView.hpp"

#include <abyss/commons/FontName.hpp>
#include <abyss/params/Cycle/SaveSelect/UserInfoParam.hpp>
#include <abyss/utils/DateTime/DateTimeUtil.hpp>

#include <Siv3D.hpp>

namespace abyss::Cycle::SaveSelect::UserInfo
{
    UserInfoView::UserInfoView():
        m_playerInfo(std::make_unique<ui::PlayerInfo::PlayerInfoExVM>())
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

        FontAsset(FontName::UserInfo)(user.getUpdatedAt().format()).draw(basePos + UserInfoParam::UpdatedAt::Pos);
    }
}
