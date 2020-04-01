#pragma once
#include <abyss/controllers/Actors/Enemy/EnemyActor.hpp>
#include <abyss/commons/Fwd.hpp>
#include <abyss/controllers/Actors/base/IState.hpp>

namespace abyss
{
    class LaunSharkActor :
        public EnemyActor
    {
    public:
        enum State
        {
            Swim,
            Launcher,
            Attack
        };
    private:
        bool m_isWait;

        StateManager<LaunSharkActor> m_state;
        std::shared_ptr<LaunSharkVM> m_view;
    public:
        LaunSharkActor(const LaunSharkEntity& entity);

        void update(double dt)override;
        void draw()const;

        void onCollisionStay(ICollider* col) override;

        bool accept(const ActVisitor& visitor) override;

        LaunSharkVM* getBindedView()const;
    };
}