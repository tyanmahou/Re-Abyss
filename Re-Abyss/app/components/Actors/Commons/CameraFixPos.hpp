#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/Ref/Ref.hpp>
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Actors/base/ILastUpdate.hpp>

namespace abyss::Actor
{
    class CameraFixPos :
        public IComponent,
        public ILastUpdate
    {
    private:
        IActor* m_pActor = nullptr;
        Ref<Body> m_body = nullptr;
    public:
        CameraFixPos(IActor* pActor);

        void onStart() override;
        void onLastUpdate() override;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::CameraFixPos>
    {
        using Base = Actor::ILastUpdate;
    };
}