#pragma once
#include <abyss/components/Actors/Commons/StateCtrl.hpp>
#include <abyss/components/Actors/Commons/Body.hpp>
#include <abyss/components/Actors/Commons/Foot.hpp>
#include <abyss/components/Actors/Commons/MapCollider.hpp>
#include <abyss/components/Actors/Commons/AudioSource.hpp>
#include <abyss/components/Actors/Player/AttackCtrl.hpp>
#include <abyss/components/Actors/Player/StateChecker.hpp>
#include <abyss/components/Actors/Commons/ViewCtrl.hpp>
#include <abyss/components/Actors/Commons/CollisionCtrl.hpp>
#include <abyss/views/Actors/Player/PlayerVM.hpp>

namespace abyss::Actor::Player
{
    class BaseState : 
        public IState
    {
    protected:
        Body* m_body;
        Foot* m_foot;
        AttackCtrl* m_attackCtrl;
        MapCollider* m_mapCol;
        CollisionCtrl* m_colCtrl;
        ViewCtrl<PlayerVM>* m_view;
        StateChecker* m_stateChecker;

        virtual void onLanding(){}
        virtual void onDraw(const PlayerVM& view)const = 0;

    public:
        void setup()override;

        Task<> start() override;

        void update() override;

        void lastUpdate() override;
        void draw() const override;
    };
}