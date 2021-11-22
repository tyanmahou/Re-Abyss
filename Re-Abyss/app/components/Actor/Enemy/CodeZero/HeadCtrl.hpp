#pragma once

#include <Siv3D/Vector2D.hpp>
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/components/Actor/Common/ILocator.hpp>
#include <abyss/components/Actor/base/ILastUpdate.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/PartsCtrl.hpp>
#include <abyss/types/Forward.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Actor::Enemy::CodeZero
{
    class HeadCtrl : 
        public IComponent,
        public ILocator,
        public ILastUpdate
    {
        Forward m_forward;

        ActorObj* m_pActor;
        Ref<Body> m_body;
        Ref<PartsCtrl> m_parts;
    public:
        HeadCtrl(ActorObj* pActor);
        void onStart() override;

        s3d::Vec2 getPos() const;

        Forward getForward() const;

        s3d::Vec2 getCenterPos() const override;

        void onLastUpdate() override;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::Enemy::CodeZero::HeadCtrl>
    {
        using Base = MultiComponents<
            Actor::ILocator,
            Actor::ILastUpdate
        >;
    };
}