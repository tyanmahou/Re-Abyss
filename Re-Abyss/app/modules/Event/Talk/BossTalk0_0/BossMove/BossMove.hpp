#pragma once
#include <abyss/utils/Ref/Ref.hpp>
#include <abyss/modules/Event/base/IEvent.hpp>

namespace abyss::Actor::Enemy::CodeZero::Demo
{
    class DemoCtrl;
}
namespace abyss::Event::Talk::BossTalk0_0
{
    class BossMove : public IEvent
    {
    public:
        void onStart()override;
        bool update(double dt) override;
        void onEnd() override;
    private:
        Ref<Actor::Enemy::CodeZero::Demo::DemoCtrl> m_codeZeroDemo;

        s3d::Vec2 m_initPos;
        s3d::Vec2 m_targetPos;
        bool m_isRequestedLastQuake = false;

        Ref<QuakeModel> m_quake;
        Ref<QuakeModel> m_lastQuake;
    public:
    };
}