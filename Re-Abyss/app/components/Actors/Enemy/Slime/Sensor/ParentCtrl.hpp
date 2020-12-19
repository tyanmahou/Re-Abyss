#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <Siv3D/Vector2D.hpp>
#include <abyss/types/Forward.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Actor::Enemy::Slime::Sensor
{
    class ParentCtrl : public IComponent
    {
        IActor* m_parent;
        Ref<StateCtrl> m_state;
        Ref<Body> m_body;
    public:
        ParentCtrl(IActor* parent);

        void onStart()override;

        bool isWalk() const;

        const s3d::Vec2& getPos() const;

        void reversed() const;

        Forward getForward() const;
    };
}