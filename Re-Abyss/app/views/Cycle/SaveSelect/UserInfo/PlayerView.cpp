#include "PlayerView.hpp"
#include <abyss/views/actors/Ooparts/base/OopartsViewUtil.hpp>

#include <Siv3D.hpp>

namespace abyss::Cycle::SaveSelect::UserInfo
{
    PlayerView::PlayerView():
        m_player(std::make_shared<Actor::Player::PlayerVM>()),
        m_ooparts(std::make_shared<Actor::Ooparts::OopartsView>())
    {
        m_oopartsCallback = std::make_shared<Actor::Ooparts::SimpleDrawCallbackView>([this]() {
            return Time::FromSec(m_time);
        });
        m_ooparts->setCallback(m_oopartsCallback);
    }
    PlayerView& PlayerView::setPos(const s3d::Vec2& pos)
    {
        m_pos = pos;
        return *this;
    }
    PlayerView& PlayerView::setTime(double time)
    {
        m_time = time;
        return *this;
    }
    PlayerView& PlayerView::setOoparts(OopartsType ooparts)
    {
        if (m_oopartsType != ooparts) {
            m_oopartsType = ooparts;
            m_ooparts->setCharacter(Actor::Ooparts::OopartsViewUtil::CreateViewFromType(m_oopartsType));
        }
        return *this;
    }
    void PlayerView::draw() const
    {
        m_oopartsCallback->update();

        if (m_oopartsType != OopartsType::Invalid) {
            auto localTarget = s3d::Vec2{ Forward::Left * -20 , -40 };
            localTarget += s3d::Vec2{
                15 * s3d::Sin(m_time * 2.0),
                10 * s3d::Sin(m_time * 4.0)
            };
            m_ooparts
                ->setPos(m_pos + localTarget)
                .setForward(Forward::Left)
                .setTime(m_time)
                .draw();
        }
        m_player
            ->setPos(m_pos)
            .setForward(Forward::Left)
            .setTime(m_time)
            .drawStateStay();
    }
}
