#pragma once
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/controllers/Actors/base/Receiver.hpp>
#include <abyss/types/Forward.hpp>

namespace abyss::CodeZero
{
    class ParentCtrlModel;
}
namespace abyss::CodeZero::Head
{
    class HeadModel;

    class HeadActor:
        public IActor,
        public Receiver
    {
    private:
        Ref<HeadModel> m_head;
        Ref<ParentCtrlModel> m_parent;
    public:
        HeadActor(IActor* parent);

        s3d::Vec2 getPos()const;

        CShape getCollider() const;
        bool accept(const ActVisitor& visitor) override;
    };
}