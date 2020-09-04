#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <Siv3D/Vector2D.hpp>
#include <abyss/types/Forward.hpp>

namespace abyss::Actor::Enemy::Slime
{
    class SlimeActor;
}
namespace abyss::Actor::Enemy::Slime::Sencer
{
    class ParentCtrl : public IComponent
    {
        SlimeActor* m_parent;
    public:
        ParentCtrl(SlimeActor* parent);

        bool isWalk() const;

        const s3d::Vec2& getPos() const;

        void reversed() const;

        Forward getForward() const;
    };
}