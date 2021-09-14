#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/Ref/Ref.hpp>
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Actor/Commons/IDeadCallback.hpp>

namespace abyss::Actor::Player
{
    class UICtrl :
        public IComponent
    {
    private:
        ActorObj* m_pActor = nullptr;
    public:
        UICtrl(ActorObj* pActor);

        void onStart() override;
    };
}