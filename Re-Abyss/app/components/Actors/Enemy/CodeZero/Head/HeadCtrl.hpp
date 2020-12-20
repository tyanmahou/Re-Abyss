#pragma once

#include <Siv3D/Vector2D.hpp>
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Actors/base/ILocator.hpp>
#include <abyss/types/Forward.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Actor::Enemy::CodeZero
{
    class ParentCtrl;
}
namespace abyss::Actor::Enemy::CodeZero::Head
{
    class HeadCtrl : 
        public IComponent,
        public ILocator
    {
        Forward m_forward;

        IActor* m_pActor;
        Ref<ParentCtrl> m_parentCtrl;
    public:
        HeadCtrl(IActor* pActor);
        void onStart() override;

        s3d::Vec2 getPos() const;

        void setForward(Forward forward);
        Forward getForward() const;

        s3d::Vec2 getCenterPos() const override;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::Enemy::CodeZero::Head::HeadCtrl>
    {
        using Base = Actor::ILocator;
    };
}