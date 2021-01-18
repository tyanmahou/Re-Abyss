#pragma once
#include <abyss/views/actors/Player/PlayerVM.hpp>
#include <abyss/views/actors/Ooparts/base/OopartsView.hpp>
#include <abyss/types/OopartsType.hpp>

namespace abyss::Cycle::SaveSelect::UserInfo
{
    class PlayerView
    {
        std::shared_ptr<Actor::Player::PlayerVM> m_player;
        std::shared_ptr<Actor::Ooparts::OopartsView> m_ooparts;

        s3d::Vec2 m_pos;

        double m_time = 0.0;
        OopartsType m_oopartsType = OopartsType::Invalid;
    public:
        PlayerView();

        PlayerView& setPos(const s3d::Vec2& pos);
        PlayerView& setTime(double time);
        PlayerView& setOoparts(OopartsType ooparts);

        void draw() const;
    };
}