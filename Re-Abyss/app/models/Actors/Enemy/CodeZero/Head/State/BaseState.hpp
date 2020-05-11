#pragma once
#include <abyss/controllers/Actors/Enemy/CodeZero/Head/HeadActor.hpp>

namespace abyss::CodeZero::Head
{
    class BaseState : public IState<HeadActor>
    {
    protected:
        HPModel* m_hp;
        CodeZeroActor* m_parent;
        HeadModel* m_head;
    public:
        void setup()override;

        void update(double dt) override;

        void draw() const override;

        void onCollisionStay(IActor* col) override;
    };
}