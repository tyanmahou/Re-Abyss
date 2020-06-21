#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/Ref/Ref.hpp>
#include <abyss/models/Actors/base/IComponent.hpp>
#include <abyss/models/Actors/base/ILastUpdateModel.hpp>

namespace abyss
{
    class CameraFixPosModel :
        public IComponent,
        public ILastUpdateModel
    {
    private:
        IActor* m_pActor = nullptr;
        Ref<BodyModel> m_body = nullptr;
    public:
        CameraFixPosModel(IActor* pActor);

        void setup() override;
        void onLastUpdate(double dt) override;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<CameraFixPosModel>
    {
        using Base = ILastUpdateModel;
    };
}