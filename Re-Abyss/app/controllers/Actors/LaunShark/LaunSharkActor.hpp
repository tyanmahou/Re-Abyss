#pragma once
#include <abyss/controllers/Actors/Enemy/EnemyActor.hpp>
#include <abyss/commons/Fwd.hpp>
#include <abyss/controllers/Actors/base/IState.hpp>
#include <abyss/models/Actors/Commons/TimeCounterModel.hpp>

#include <abyss/views/Actors/LaunShark/LaunSharkVM.hpp>

namespace abyss
{
    struct LaunSharkEntity;
}
namespace abyss::LaunShark
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
        TimeCounterModel m_timeCounter;
        StateManager<LaunSharkActor> m_state;
        std::shared_ptr<LaunSharkVM> m_view;
    public:
        LaunSharkActor(const LaunSharkEntity& entity);

        void update(double dt)override;
        void lastUpdate(double dt)override;
        void draw()const;

        void onCollisionStay(ICollider* col) override;

        bool accept(const ActVisitor& visitor) override;

        LaunSharkVM* getBindedView()const;
    };
}