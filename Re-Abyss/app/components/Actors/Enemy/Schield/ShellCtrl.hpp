#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Actors/base/IDeadCallback.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Actor::Enemy::Schield
{
    class ShellCtrl :
        public IComponent,
        public IDeadCallback
    {
        IActor* m_pActor;
        Ref<IActor> m_shell;
    public:
        ShellCtrl(IActor* pActor);
        ~ShellCtrl();

        void onStart() override;
        void onEnd() override;
        void onDead() override;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::Enemy::Schield::ShellCtrl>
    {
        using Base = Actor::IDeadCallback;
    };
}