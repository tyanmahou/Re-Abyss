#pragma once
#include <abyss/controllers/Actors/Enemy/CaptainTako/Shot/ShotActor.hpp>
#include <abyss/models/Actors/base/StateModel.hpp>

namespace abyss::CaptainTako::Shot
{

    class BaseState : public IState
    {
    protected:
        BodyModel* m_body;
    public:
        void setup()override;

        void start() override;

        void update(double dt) override;
    };
}