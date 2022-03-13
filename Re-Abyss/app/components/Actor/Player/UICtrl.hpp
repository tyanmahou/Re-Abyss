#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/Ref/Ref.hpp>
#include <abyss/modules/GameObject/IComponent.hpp>

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