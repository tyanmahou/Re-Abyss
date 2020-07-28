#pragma once
#include <abyss/controllers/Actors/Player/PlayerActor.hpp>
#include <abyss/models/Actors/Commons/MapColliderModel.hpp>
#include <abyss/models/Actors/Player/AttackCtrlModel.hpp>
#include <abyss/models/Actors/Commons/ViewModel.hpp>
#include <abyss/views/Actors/Player/PlayerVM.hpp>

namespace abyss::Player
{
    using Floor::FloorActor;
    using PenetrateFloor::PenetrateFloorActor;
    using Ladder::LadderActor;
    using Door::DoorActor;

    class BaseState : public IOldState<PlayerActor>
    {
    protected:
        BodyModel* m_body;
        FootModel* m_foot;
        ChargeModel* m_charge;
        HPModel* m_hp;
        AttackCtrlModel* m_attackCtrl;
        MapColliderModel* m_mapCol;

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