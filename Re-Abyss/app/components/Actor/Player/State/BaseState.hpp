#pragma once
#include <abyss/components/Actor/Commons/StateCtrl.hpp>
#include <abyss/components/Actor/Commons/Body.hpp>
#include <abyss/components/Actor/Commons/Foot.hpp>
#include <abyss/components/Actor/Commons/MapCollider.hpp>
#include <abyss/components/Actor/Commons/AudioSource.hpp>
#include <abyss/components/Actor/Player/AttackCtrl.hpp>
#include <abyss/components/Actor/Player/StateChecker.hpp>
#include <abyss/components/Actor/Commons/ViewCtrl.hpp>
#include <abyss/components/Actor/Commons/CollisionCtrl.hpp>
#include <abyss/views/Actor/Player/PlayerVM.hpp>

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