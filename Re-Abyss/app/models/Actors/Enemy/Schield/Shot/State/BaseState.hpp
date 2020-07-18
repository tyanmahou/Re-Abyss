#pragma once
#include <abyss/models/Actors/Commons/StateModel.hpp>
#include <abyss/models/Actors/Commons/BodyModel.hpp>

namespace abyss::Schield::Shot
{

    class BaseState : public IState
    {
    protected:
        BodyModel* m_body;
    public:
        void setup()override;

        void start() override;
    };
}