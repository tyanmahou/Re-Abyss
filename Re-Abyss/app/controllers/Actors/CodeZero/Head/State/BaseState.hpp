#pragma once
#include <abyss/controllers/Actors/CodeZero/Head/HeadActor.hpp>

namespace abyss::CodeZero::Head
{
    class BaseState : public IState<HeadActor>
    {
    protected:
        HPModel* m_hp;
        CodeZeroActor* m_parent;
        Forward* m_forward;
    public:
        void setup()override;

        void update(double dt) override;

        void draw() const override;

        void onCollisionStay(ICollider* col) override;
    };
}