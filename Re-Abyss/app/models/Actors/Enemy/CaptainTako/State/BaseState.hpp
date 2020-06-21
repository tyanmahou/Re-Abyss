#pragma once
#include <abyss/controllers/Actors/Enemy/CaptainTako/CaptainTakoActor.hpp>

namespace abyss::CaptainTako
{
    class BaseState : public IState<CaptainTakoActor>
    {
    protected:
        BodyModel* m_body;

    public:
        void setup()override;

        void update(double dt) override;

        void draw() const override;
    };
}