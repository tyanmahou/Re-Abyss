#pragma once
#if ABYSS_DEBUG
#include <abyss/commons/Fwd.hpp>
#include <abyss/models/Actors/base/IComponent.hpp>
#include <abyss/models/Actors/base/IUpdateModel.hpp>

namespace abyss::Player
{
    class DebugCtrlModel :
        public IComponent,
        public IUpdateModel
    {
    private:
        IActor* m_pActor;
    public:
        DebugCtrlModel(IActor* pActor);

        void setup() override;
        void onUpdate(double dt) override;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Player::DebugCtrlModel>
    {
        using Base = IUpdateModel;
    };
}

#endif