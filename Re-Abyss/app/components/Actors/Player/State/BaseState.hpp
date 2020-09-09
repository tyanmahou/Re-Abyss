#pragma once
#include <abyss/models/Actors/Commons/StateModel.hpp>
#include <abyss/models/Actors/Commons/BodyModel.hpp>
#include <abyss/components/Actors/Commons/Foot.hpp>
#include <abyss/models/Actors/Commons/HPModel.hpp>
#include <abyss/components/Actors/Commons/MapCollider.hpp>
#include <abyss/components/Actors/Commons/AudioSource.hpp>
#include <abyss/components/Actors/Player/ChargeCtrl.hpp>
#include <abyss/components/Actors/Player/AttackCtrl.hpp>
#include <abyss/components/Actors/Commons/ViewCtrl.hpp>
#include <abyss/views/Actors/Player/PlayerVM.hpp>

namespace abyss::Actor::Player
{
    using Actor::Map::Floor::FloorActor;
    using Actor::Map::PenetrateFloor::PenetrateFloorActor;
    using Actor::Map::Ladder::LadderActor;
    using Actor::Gimmick::Door::DoorActor;

    class BaseState : public IState
    {
    protected:
        BodyModel* m_body;
        Foot* m_foot;
        ChargeCtrl* m_charge;
        HPModel* m_hp;
        AttackCtrl* m_attackCtrl;
        MapCollider* m_mapCol;
        ViewCtrl<PlayerVM>* m_view;

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