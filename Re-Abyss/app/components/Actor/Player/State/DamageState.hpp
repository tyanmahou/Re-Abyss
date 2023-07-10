#pragma once
#include <abyss/components/Actor/Player/State/BaseState.hpp>

namespace abyss::Actor::Player
{
    class DamageState final : public BaseState
    {
        void start()override;
        Fiber<> updateAsync()override;
        void update()override;
    public:
        DamageState(const s3d::Vec2& velocity);

    private:
        const s3d::Vec2 m_velocity;
    };
}
