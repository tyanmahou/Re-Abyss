#pragma once
#include <abyss/models/Actors/Commons/StateModel.hpp>
#include <abyss/models/Actors/Commons/BodyModel.hpp>
#include <abyss/components/Actors/Commons/AudioSource.hpp>
#include <abyss/models/Actors/Commons/MapColliderModel.hpp>
#include <abyss/models/Actors/Commons/ViewModel.hpp>

#include <abyss/views/Actors/Enemy/Slime/SlimeVM.hpp>

namespace abyss::Actor::Enemy::Slime
{

    class BaseState : public IState
    {
    protected:
        BodyModel* m_body;
        MapColliderModel* m_mapCol;
        ViewModel<SlimeVM>* m_view;
    public:
        void setup()override;

        void update(double dt) override;
        void lastUpdate();
    };
}