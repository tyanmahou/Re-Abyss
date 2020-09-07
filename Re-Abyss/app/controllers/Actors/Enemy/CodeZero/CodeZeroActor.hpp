#pragma once
#include <abyss/controllers/Actors/Enemy/EnemyActor.hpp>
#include <abyss/commons/Fwd.hpp>

namespace abyss
{
    struct CodeZeroEntity;
}
namespace abyss::Actor::Enemy::CodeZero
{
    class PartsCtrl;

    class CodeZeroActor :
        public EnemyActor
    {
    private:
        Ref<PartsCtrl> m_parts;
    public:
        CodeZeroActor(const CodeZeroEntity& entity);

        bool accept(const ActVisitor& visitor) override;

        void setActiveAll(bool active);
    };
}