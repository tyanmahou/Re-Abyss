#pragma once
#include <abyss/models/Actors/Commons/BodyModel.hpp>
#include <abyss/models/Actors/Commons/AudioSourceModel.hpp>
#include <abyss/models/Actors/Commons/StateModel.hpp>
#include <abyss/models/Actors/Commons/ViewModel.hpp>

#include <abyss/views/Actors/Enemy/RollingTako/RollingTakoVM.hpp>

namespace abyss::Actor::Enemy::RollingTako
{
    class BaseState : public IState
    {
    protected:
        BodyModel* m_body;
        MapColliderModel* m_mapCol;
        ViewModel<RollingTakoVM>* m_view;
    public:
        void setup()override;

        void lastUpdate() override;
    };
}
