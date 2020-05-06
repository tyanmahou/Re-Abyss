#pragma once
#include <memory>
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
        std::weak_ptr<CodeZero::Demo::DemoActor> m_codeZero;

        s3d::Vec2 m_initPos;
        s3d::Vec2 m_targetPos;
    public:
        ~BossMove();
    };
}