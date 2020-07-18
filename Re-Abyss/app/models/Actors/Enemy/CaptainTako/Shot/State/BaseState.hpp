#pragma once
#include <abyss/models/Actors/Commons/StateModel.hpp>

namespace abyss::CaptainTako::Shot
{

    class BaseState : public IState
    {
    public:
        void setup()override;

        void start() override;
    };
}