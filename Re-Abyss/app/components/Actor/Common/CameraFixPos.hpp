#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/Ref/Ref.hpp>
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/modules/Actor/base/ILastUpdate.hpp>

namespace abyss::Actor
{
    class CameraFixPos :
        public IComponent,
        public ILastUpdate
    {
    private:
        ActorObj* m_pActor = nullptr;
        Ref<Body> m_body = nullptr;
    public:
        CameraFixPos(ActorObj* pActor);

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