#pragma once
#include <abyss/utils/Ref/Ref.hpp>
#include <abyss/controllers/Event/base/IEvent.hpp>

namespace abyss::Actor::Enemy::CodeZero::Demo
{
    class DemoActor;
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
        Ref<Actor::Enemy::CodeZero::Demo::DemoActor> m_codeZero;

        s3d::Vec2 m_initPos;
        s3d::Vec2 m_targetPos;
        bool m_isRequestedLastQuake = false;

        Ref<QuakeModel> m_quake;
        Ref<QuakeModel> m_lastQuake;
    public:
    };
}