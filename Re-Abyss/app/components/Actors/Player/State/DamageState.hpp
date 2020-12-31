#pragma once
#include"BaseState.hpp"

namespace abyss::Actor::Player
{
    class DamageState final : public BaseState
    {
        Task<> start()override;
        void update()override;
        void onDraw(const PlayerVM& view)const override;
    public:
        DamageState(const s3d::Vec2& velocity);

    private:
        const s3d::Vec2 m_velocity;
    };
}