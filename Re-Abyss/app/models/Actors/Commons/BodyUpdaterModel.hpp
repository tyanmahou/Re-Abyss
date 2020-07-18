#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/Ref/Ref.hpp>
#include <abyss/models/Actors/base/IComponent.hpp>
#include <abyss/models/Actors/base/IMoveModel.hpp>

namespace abyss
{
    class BodyUpdaterModel :
        public IComponent,
        public IMoveModel
    {
    private:
        IActor* m_pActor = nullptr;
        Ref<BodyModel> m_body;

        bool m_isActive = true;
    public:
        BodyUpdaterModel(IActor* pActor);

        void setup() override;
        void onMove(double dt) override;

        BodyUpdaterModel& setActive(bool isActive)
        {
            m_isActive = isActive;
            return *this;
        }
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<BodyUpdaterModel>
    {
        using Base = IMoveModel;
    };
}