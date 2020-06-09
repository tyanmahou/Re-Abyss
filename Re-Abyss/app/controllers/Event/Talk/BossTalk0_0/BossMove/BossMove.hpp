#pragma once
#include <abyss/utils/Ref/Ref.hpp>
#include <abyss/controllers/Event/base/IEvent.hpp>

namespace abyss::CodeZero::Demo
{
    class DemoActor;
}
namespace abyss::Event::Talk::BossTalk0_0
{
    class BossMove : public IEvent
    {
        void init()override;
        bool update(double dt) override;
    private:
        Ref<CodeZero::Demo::DemoActor> m_codeZero;

        s3d::Vec2 m_initPos;
        s3d::Vec2 m_targetPos;
        bool m_isRequestedLastQuake = false;
    public:
        ~BossMove();
    };
}