#pragma once
#include <abyss/views/Actor/Player/PlayerVM.hpp>
#include <abyss/views/Actor/Ooparts/base/OopartsView.hpp>
#include <abyss/views/Actor/Ooparts/base/SimpleDrawCallbackView.hpp>
#include <abyss/types/OopartsType.hpp>

namespace abyss::Cycle::SaveSelect::UserInfo
{
    class PlayerView
    {
        std::shared_ptr<Actor::Player::PlayerVM> m_player;
        std::shared_ptr<Actor::Ooparts::OopartsView> m_ooparts;
        std::shared_ptr<Actor::Ooparts::SimpleDrawCallbackView> m_oopartsCallback;

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