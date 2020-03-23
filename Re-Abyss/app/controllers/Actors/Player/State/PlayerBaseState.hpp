#pragma once
#include <abyss/controllers/Actors/Player/PlayerActor.hpp>

namespace abyss
{
    class PlayerBaseState : public IState<PlayerActor>
    {
    protected:
        BodyModel* m_body;
        FootModel* m_foot;
        ChargeModel* m_charge;

        virtual void onMove(double dt);
        virtual void onLanding(){}
        virtual void onDraw(const PlayerVM& view)const = 0;
        ColDirection fixPos(const MapColInfo& mapColInfo);

        virtual void onCollisionStay(const FloorActor& col);
        virtual void onCollisionStay(const PenetrateFloorActor& col);
        virtual void onCollisionStay(const LadderActor& ladder);
        virtual void onCollisionStayLadderTop(const LadderActor& ladder);
        virtual void onCollisionStay(const DoorActor& col);

    public:
        void setup()override;

        void start() override;

        void update(double dt) override;

        void onCollisionStay(ICollider* col) override;

        void draw() const override;
    };
}