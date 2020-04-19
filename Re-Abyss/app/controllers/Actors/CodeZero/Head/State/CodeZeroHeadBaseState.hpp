#pragma once
#include <abyss/controllers/Actors/CodeZero/Head/CodeZeroHeadActor.hpp>

namespace abyss
{
    class CodeZeroHeadBaseState : public IState<CodeZeroHeadActor>
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