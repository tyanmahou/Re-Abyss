#pragma once
#include <abyss/models/Actors/Commons/StateModel.hpp>
#include <abyss/models/Actors/Commons/BodyModel.hpp>
#include <abyss/models/Actors/Commons/FootModel.hpp>
#include <abyss/models/Actors/Commons/HPModel.hpp>
#include <abyss/models/Actors/Commons/MapColliderModel.hpp>
#include <abyss/models/Actors/Commons/AudioSourceModel.hpp>
#include <abyss/models/Actors/Player/ChargeModel.hpp>
#include <abyss/models/Actors/Player/AttackCtrlModel.hpp>
#include <abyss/models/Actors/Commons/ViewModel.hpp>
#include <abyss/views/Actors/Player/PlayerVM.hpp>

namespace abyss::Player
{
    using Floor::FloorActor;
    using PenetrateFloor::PenetrateFloorActor;
    using Ladder::LadderActor;
    using Actor::Gimmick::Door::DoorActor;

    class BaseState : public IState
    {
    protected:
        BodyModel* m_body;
        FootModel* m_foot;
        ChargeModel* m_charge;
        HPModel* m_hp;
        AttackCtrlModel* m_attackCtrl;
        MapColliderModel* m_mapCol;
        ViewModel<PlayerVM>* m_view;

        virtual void onMove(double dt);
        virtual void onLanding(){}
        virtual void onDraw(const PlayerVM& view)const = 0;

        virtual void onCollisionStay(const PenetrateFloorActor& col);
        virtual void onCollisionStay(const LadderActor& ladder);
        virtual void onCollisionStayLadderTop(const LadderActor& ladder);
        virtual void onCollisionStay(const DoorActor& col);

    public:
        void setup()override;

        void start() override;

        void update(double dt) override;

        void onCollisionStay(IActor* col) override;

        void lastUpdate() override;
        void draw() const override;
    };
}