#pragma once
#include <abyss/controllers/Actors/Enemy/EnemyActor.hpp>
#include <abyss/commons/Fwd.hpp>
#include <abyss/models/Actors/base/StateModel.hpp>

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

        std::shared_ptr<CaptainTakoVM> m_view;
    public:
        CaptainTakoActor(const CaptainTakoEntity& entity);

        bool accept(const ActVisitor& visitor) override;

        CaptainTakoVM* getBindedView()const;
    };
}