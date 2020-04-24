#pragma once
#include <abyss/controllers/Actors/CodeZero/CodeZeroActor.hpp>

namespace abyss::CodeZero
{
    class BaseState : public IState<CodeZeroActor>
    {
    protected:
        HPModel* m_hp;
    public:
        BaseState();
        void setup()override;

        void update(double dt) override;

        void draw() const override;
    };
}