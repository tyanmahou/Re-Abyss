#pragma once
#if ABYSS_DEBUG
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/base/IComponent.hpp>
#include <abyss/models/Actors/base/IUpdateModel.hpp>

namespace abyss::Actor::Player
{
    class DebugCtrl :
        public IComponent,
        public IUpdateModel
    {
    private:
        IActor* m_pActor;
    public:
        DebugCtrl(IActor* pActor);

        void setup() override;
        void onUpdate(double dt) override;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::Player::DebugCtrl>
    {
        using Base = IUpdateModel;
    };
}

#endif