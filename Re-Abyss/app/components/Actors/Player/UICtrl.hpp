#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/Ref/Ref.hpp>
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Actors/base/IDeadCallback.hpp>

namespace abyss::Actor::Player
{
    class UICtrl :
        public IComponent
    {
    private:
        IActor* m_pActor = nullptr;
    public:
        UICtrl(IActor* pActor);

        void onStart() override;
    };
}