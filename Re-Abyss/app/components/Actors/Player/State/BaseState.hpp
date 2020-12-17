#pragma once
#include <abyss/components/Actors/Commons/StateCtrl.hpp>
#include <abyss/components/Actors/Commons/Body.hpp>
#include <abyss/components/Actors/Commons/Foot.hpp>
#include <abyss/components/Actors/Commons/HP.hpp>
#include <abyss/components/Actors/Commons/MapCollider.hpp>
#include <abyss/components/Actors/Commons/AudioSource.hpp>
#include <abyss/components/Actors/Player/ChargeCtrl.hpp>
#include <abyss/components/Actors/Player/AttackCtrl.hpp>
#include <abyss/components/Actors/Commons/ViewCtrl.hpp>
#include <abyss/components/Actors/Commons/CollisionCtrl.hpp>
#include <abyss/components/Actors/Map/PenetrateFloorProxy/PenetrateFloorProxy.hpp>
#include <abyss/components/Actors/Map/Ladder/LadderProxy.hpp>
#include <abyss/components/Actors/Gimmick/Door/DoorProxy.hpp>
#include <abyss/views/Actors/Player/PlayerVM.hpp>
#include <abyss/components/Actors/base/ICollisionReact.hpp>

namespace abyss::Actor::Player
{
    using Actor::Map::Floor::FloorActor;
    using Actor::Map::PenetrateFloor::PenetrateFloorProxy;
    using Actor::Map::Ladder::LadderProxy;
    using Actor::Gimmick::Door::DoorProxy;

    class BaseState : 
        public IState,
        public ICollisionReact
    {
    protected:
        Body* m_body;
        Foot* m_foot;
        ChargeCtrl* m_charge;
        HP* m_hp;
        AttackCtrl* m_attackCtrl;
        MapCollider* m_mapCol;
        CollisionCtrl* m_colCtrl;
        ViewCtrl<PlayerVM>* m_view;

        virtual void onMove(double dt);
        virtual void onLanding(){}
        virtual void onDraw(const PlayerVM& view)const = 0;

        virtual bool onCollisionStay(const PenetrateFloorProxy& col);
        virtual bool onCollisionStay(const LadderProxy& ladder);
        virtual bool onCollisionStayLadderTop(const LadderProxy& ladder);
        virtual bool onCollisionStay(const DoorProxy& col);

    public:
        void setup()override;

        void start() override;

        void update() override;

        void onCollisionReact() override;

        void lastUpdate() override;
        void draw() const override;
    };
}