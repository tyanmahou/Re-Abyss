#pragma once
#include <abyss/models/Actors/Commons/StateModel.hpp>

#include <abyss/models/Actors/Commons/BodyModel.hpp>
#include <abyss/models/Actors/Commons/MapColliderModel.hpp>
#include <abyss/models/Actors/Commons/TimeCounterModel.hpp>
#include <abyss/models/Actors/Commons/ViewModel.hpp>
#include <abyss/views/Actors/Enemy/LaunShark/LaunSharkVM.hpp>

namespace abyss::LaunShark
{
    class BaseState : public IState
    {
    protected:
        BodyModel* m_body;
        MapColliderModel* m_mapCol;
        TimeCounterModel* m_timeCounter;
        ViewModel<LaunSharkVM>* m_view;
    public:
        void update(double dt) override;
        void setup()override;

        void lastUpdate() override;
    };
}
