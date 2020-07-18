#pragma once
#include <abyss/controllers/Actors/Enemy/EnemyActor.hpp>
#include <abyss/commons/Fwd.hpp>
#include <abyss/models/Actors/Commons/RotateModel.hpp>
#include <abyss/models/Actors/base/OldStateModel.hpp>

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
        Ref<RotateModel> m_rotate;
        std::shared_ptr<IkalienVM> m_view;
    public:
        IkalienActor(const IkalienEntity& entity);

        CShape getCollider() const;

        bool accept(const ActVisitor& visitor) override;

        IkalienVM* getBindedView()const;
    };
}