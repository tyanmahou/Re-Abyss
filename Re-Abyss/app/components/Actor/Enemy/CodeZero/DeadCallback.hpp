#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/components/Actor/Common/IDeadCallback.hpp>
#include <Siv3D/Optional.hpp>
#include <Siv3D/String.hpp>

namespace abyss::Actor::Enemy::CodeZero
{
    class DeadCallback :
        public IComponent,
        public IDeadCallback
    {
    public:
        DeadCallback(ActorObj* pActor);

        void setDeadEventPath(const s3d::String& path);
    public:
        void onDead() override;

    private:
        ActorObj* m_pActor;
        s3d::Optional<s3d::String> m_deadEventPath;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::Enemy::CodeZero::DeadCallback>
    {
        using Base = Actor::IDeadCallback;
    };
}