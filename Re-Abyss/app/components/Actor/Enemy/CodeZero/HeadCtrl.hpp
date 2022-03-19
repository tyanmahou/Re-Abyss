#pragma once

#include <Siv3D/Vector2D.hpp>
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/components/Actor/Common/ILocator.hpp>
#include <abyss/components/Actor/base/ILastUpdate.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/PartsCtrl.hpp>
#include <abyss/types/Look.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Actor::Enemy::CodeZero
{
    class HeadCtrl : 
        public IComponent,
        public ILocator,
        public ILastUpdate
    {
    public:
        HeadCtrl(ActorObj* pActor);

        s3d::Vec2 getPos() const;

        const Look& getLook() const;
        s3d::Vec2 getCenterPos() const override;

        void setActive(bool isActive);

        void onStart() override;

        void onLastUpdate() override;
    private:
        ActorObj* m_pActor;
        Ref<Body> m_body;
        Ref<PartsCtrl> m_parts;

        bool m_isActive = true;
        Look m_look;
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