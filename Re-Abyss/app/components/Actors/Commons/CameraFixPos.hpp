#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/Ref/Ref.hpp>
#include <abyss/components/base/IComponent.hpp>
#include <abyss/models/Actors/base/ILastUpdateModel.hpp>

namespace abyss::Actor
{
    class CameraFixPos :
        public IComponent,
        public ILastUpdateModel
    {
    private:
        IActor* m_pActor = nullptr;
        Ref<Body> m_body = nullptr;
    public:
        CameraFixPos(IActor* pActor);

        void setup() override;
        void onLastUpdate() override;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::CameraFixPos>
    {
        using Base = ILastUpdateModel;
    };
}