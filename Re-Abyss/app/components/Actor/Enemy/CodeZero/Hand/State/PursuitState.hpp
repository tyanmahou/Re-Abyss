#pragma once
#include <abyss/components/Actor/Enemy/CodeZero/Hand/State/BaseState.hpp>

namespace abyss::Actor::Enemy::CodeZero::Hand
{
    class PursuitState final : public BaseState
    { 
    public:
        PursuitState(const s3d::Optional<HandDesc>& desc = s3d::none, bool slowStart = false);
        void update() override;
        void start()override;
        void lastUpdate() override;
    private:
        s3d::Optional<HandDesc> m_desc;
        bool m_slowStart = false;
    };
}