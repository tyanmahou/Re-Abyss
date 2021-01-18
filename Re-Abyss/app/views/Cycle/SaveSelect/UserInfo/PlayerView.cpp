#include "PlayerView.hpp"

namespace abyss::Cycle::SaveSelect::UserInfo
{
    PlayerView::PlayerView():
        m_player(std::make_shared<Actor::Player::PlayerVM>())
    {}
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
    void PlayerView::draw() const
    {
        m_player
            ->setPos(m_pos)
            .setTime(m_time)
            .drawStateStay();
    }
}
