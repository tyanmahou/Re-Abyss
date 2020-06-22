#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/Ref/Ref.hpp>
#include <abyss/models/Actors/base/IComponent.hpp>
#include <abyss/models/Actors/base/ILastUpdateModel.hpp>

namespace abyss::Player
{
    class DeadCheckerModel :
        public IComponent,
        public ILastUpdateModel
    {
    private:
        IActor* m_pActor = nullptr;
        Ref<HPModel> m_hp;
    public:
        DeadCheckerModel(IActor* pActor);

        void setup() override;
        void onLastUpdate(double dt) override;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Player::DeadCheckerModel>
    {
        using Base = ILastUpdateModel;
    };
}