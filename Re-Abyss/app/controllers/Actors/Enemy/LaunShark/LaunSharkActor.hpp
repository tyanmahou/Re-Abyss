#pragma once
#include <abyss/controllers/Actors/Enemy/EnemyActor.hpp>
#include <abyss/commons/Fwd.hpp>
#include <abyss/models/Actors/base/StateModel.hpp>
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
        std::shared_ptr<LaunSharkVM> m_view;
    public:
        LaunSharkActor(const LaunSharkEntity& entity);

        bool accept(const ActVisitor& visitor) override;

        LaunSharkVM* getBindedView()const;
    };
}