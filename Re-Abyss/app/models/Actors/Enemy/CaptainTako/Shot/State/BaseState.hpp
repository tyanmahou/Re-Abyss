#pragma once
#include <abyss/models/Actors/Commons/StateModel.hpp>

#include <abyss/models/Actors/Commons/ViewModel.hpp>
#include <abyss/views/Actors/Enemy/CaptainTako/Shot/ShotVM.hpp>

namespace abyss::CaptainTako::Shot
{

    class BaseState : public IState
    {
        ViewModel<ShotVM>* m_view;
    public:
        void setup()override;

        void start() override;

        void draw() const override;
    };
}