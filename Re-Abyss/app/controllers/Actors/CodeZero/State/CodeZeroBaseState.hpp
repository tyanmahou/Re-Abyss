#pragma once
#include <abyss/controllers/Actors/CodeZero/CodeZeroActor.hpp>

namespace abyss
{
    class CodeZeroBaseState : public IState<CodeZeroActor>
    {
    protected:
        HPModel* m_hp;
    public:
        CodeZeroBaseState();
        void setup()override;

        void update(double dt) override;

        void draw() const override;
    };
}