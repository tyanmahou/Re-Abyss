#pragma once
#include <abyss/models/Actors/Commons/StateModel.hpp>
#include <abyss/models/Actors/Commons/BodyModel.hpp>
#include <abyss/models/Actors/Commons/RotateModel.hpp>
#include <abyss/models/Actors/Commons/ViewModel.hpp>
#include <abyss/views/Actors/Enemy/Ikalien/IkalienVM.hpp>

namespace abyss::Actor::Ikalien
{
    class BaseState : public IState
    {
    protected:
        BodyModel* m_body;
        RotateModel* m_rotate;
        ViewModel<IkalienVM>* m_view;
    public:
        void setup()override;
    };
}
