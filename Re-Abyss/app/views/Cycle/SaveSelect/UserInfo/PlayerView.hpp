#pragma once
#include <abyss/views/actors/Player/PlayerVM.hpp>

namespace abyss::Cycle::SaveSelect::UserInfo
{
    class PlayerView
    {
        std::shared_ptr<Actor::Player::PlayerVM> m_player;

        s3d::Vec2 m_pos;
        double m_time = 0.0;
    public:
        PlayerView();

        PlayerView& setPos(const s3d::Vec2& pos);
        PlayerView& setTime(double time);

        void draw() const;
    };
}