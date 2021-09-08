#pragma once
#include"BaseState.hpp"

namespace abyss::Actor::Player
{
    class DamageState final : public BaseState
    {
        void start()override;
        Task<> task()override;
        void update()override;
    public:
        DamageState(const s3d::Vec2& velocity);

    private:
        const s3d::Vec2 m_velocity;
    };
}