#pragma once
#include <abyss/controllers/Actors/Enemy/EnemyActor.hpp>
#include <abyss/commons/Fwd.hpp>
#include <abyss/models/Actors/base/OldStateModel.hpp>

namespace abyss
{
    struct RollingTakoEntity;
}

namespace abyss::RollingTako
{
    class RollingTakoVM;

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

        Ref<OldStateModel<RollingTakoActor>> m_state;
        std::shared_ptr<RollingTakoVM> m_view;
    public:
        RollingTakoActor(const RollingTakoEntity& entity);

        bool accept(const ActVisitor& visitor) override;

        RollingTakoVM* getBindedView()const;
    };
}