#pragma once
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/controllers/Actors/base/Receiver.hpp>
#include <abyss/types/Forward.hpp>

namespace abyss::Actor::Enemy::CodeZero
{
    class ParentCtrl;
}
namespace abyss::Actor::Enemy::CodeZero::Head
{
    class HeadCtrl;

    class HeadActor:
        public IActor,
        public Receiver
    {
    private:
        Ref<HeadCtrl> m_head;
        Ref<ParentCtrl> m_parent;
    public:
        HeadActor(IActor* parent);

        s3d::Vec2 getPos()const;

        CShape getCollider() const;
        bool accept(const ActVisitor& visitor) override;
    };
}