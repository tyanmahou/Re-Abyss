#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/Ref/Ref.hpp>
#include <abyss/models/Actors/base/IComponent.hpp>
#include <abyss/models/Actors/base/ILastUpdateModel.hpp>

namespace abyss
{
    class FallCheckerModel :
        public IComponent,
        public ILastUpdateModel
    {
    private:
        IActor* m_pActor = nullptr;
        Ref<DeadCheckerModel> m_deadChecker;
        Ref<BodyModel> m_body;

        bool m_isFall = false;
    public:
        FallCheckerModel(IActor* pActor);

        void setup() override;
        void onLastUpdate() override;

        bool isFall() const
        {
            return m_isFall;
        }
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<FallCheckerModel>
    {
        using Base = ILastUpdateModel;
    };
}