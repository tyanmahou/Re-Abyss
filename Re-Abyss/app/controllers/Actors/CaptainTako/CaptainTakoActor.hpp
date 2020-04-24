#pragma once
#include <abyss/controllers/Actors/Enemy/EnemyActor.hpp>
#include <abyss/commons/Fwd.hpp>
#include <abyss/controllers/Actors/base/IState.hpp>

namespace abyss
{
    struct CaptainTakoEntity;
}
namespace abyss::CaptainTako
{
    class CaptainTakoVM;

    class CaptainTakoActor :
        public EnemyActor
    {
    public:
        enum State
        {
            Wait,
            Charge,
            Attack,
        };
    private:
        bool m_isWait;

        StateManager<CaptainTakoActor> m_state;
        std::shared_ptr<CaptainTakoVM> m_view;
    public:
        CaptainTakoActor(const CaptainTakoEntity& entity);

        void update(double dt)override;
        void draw()const;

        void onCollisionStay(ICollider* col) override;

        bool accept(const ActVisitor& visitor) override;

        CaptainTakoVM* getBindedView()const;
    };
}