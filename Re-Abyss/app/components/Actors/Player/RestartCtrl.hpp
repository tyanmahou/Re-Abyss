#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/Ref/Ref.hpp>
#include <abyss/components/base/IComponent.hpp>
#include <abyss/models/Actors/base/IDeadCallbackModel.hpp>

namespace abyss::Actor::Player
{
    class RestartCtrl :
        public IComponent,
        public IDeadCallbackModel
    {
    private:
        IActor* m_pActor = nullptr;
    public:
        RestartCtrl(IActor* pActor);

        void setup() override;
        void onDead() override;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::Player::RestartCtrl>
    {
        using Base = IDeadCallbackModel;
    };
}