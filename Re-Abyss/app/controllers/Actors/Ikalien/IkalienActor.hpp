#pragma once
#include <abyss/controllers/Actors/Enemy/EnemyActor.hpp>
#include <abyss/commons/Fwd.hpp>
#include <abyss/controllers/Actors/base/IState.hpp>
#include <abyss/models/Actors/Commons/RotateModel.hpp>

namespace abyss
{
    struct IkalienEntity;
}
namespace abyss::Ikalien
{
    class IkalienVM;

    class IkalienActor :
        public EnemyActor
    {
    public:
        enum State
        {
            Wait,
            Pursuit,
            Swim,
        };
    private:
        RotateModel m_rotate;
        StateManager<IkalienActor> m_state;
        std::shared_ptr<IkalienVM> m_view;
    public:
        IkalienActor(const IkalienEntity& entity);

        void update(double dt)override;
        void draw()const;

        CShape getCollider() const override;
        void onCollisionStay(ICollider* col) override;

        bool accept(const ActVisitor& visitor) override;

        IkalienVM* getBindedView()const;
    };
}