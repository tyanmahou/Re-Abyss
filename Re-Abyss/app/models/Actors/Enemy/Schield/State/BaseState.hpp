#pragma once
#include <abyss/controllers/Actors/Enemy/Schield/SchieldActor.hpp>

namespace abyss::Schield
{
    class BaseState : public IState<SchieldActor>
    {
    protected:
        BodyModel* m_body;

    public:
        void setup()override;

        void update(double dt) override;
    };
}
