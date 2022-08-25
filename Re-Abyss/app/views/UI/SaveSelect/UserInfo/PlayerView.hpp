#pragma once
#include <abyss/views/Actor/Player/PlayerVM.hpp>
#include <abyss/views/Actor/Ooparts/base/OopartsView.hpp>
#include <abyss/entities/OopartsType.hpp>

namespace abyss::UI::SaveSelect::UserInfo
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

        s3d::Vec2 getOopartsPos() const;

        void draw() const;
    };
}
