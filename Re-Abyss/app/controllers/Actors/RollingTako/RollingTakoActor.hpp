#pragma once
#include <abyss/controllers/Actors/Enemy/EnemyActor.hpp>
#include <abyss/commons/Fwd.hpp>
#include <abyss/controllers/Actors/base/IState.hpp>

namespace abyss
{
    class RollingTakoActor :
        public EnemyActor
    {
    public:
        enum State
        {
            Wait,
            Run
        };
    private:
        bool m_isWait;

        StateManager<RollingTakoActor> m_state;
        std::shared_ptr<RollingTakoVM> m_view;
    public:
        RollingTakoActor(const RollingTakoEntity& entity);

        void update(double dt)override;
        void lastUpdate(double dt) override;
        void draw()const;

        void onCollisionStay(ICollider* col) override;

        bool accept(const ActVisitor& visitor) override;

        RollingTakoVM* getBindedView()const;
    };
}