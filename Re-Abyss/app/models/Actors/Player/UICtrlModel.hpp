#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/Ref/Ref.hpp>
#include <abyss/components/base/IComponent.hpp>
#include <abyss/models/Actors/base/IDeadCallbackModel.hpp>

namespace abyss::Actor::Player
{
    class UICtrlModel :
        public IComponent
    {
    private:
        IActor* m_pActor = nullptr;
    public:
        UICtrlModel(IActor* pActor);

        void onStart() override;
    };
}