#pragma once
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/controllers/Actors/base/Receiver.hpp>
#include <abyss/types/Forward.hpp>
#include <abyss/models/Actors/base/OldStateModel.hpp>
#include <abyss/models/Actors/Enemy/CodeZero/ParentCtrlModel.hpp>
#include <abyss/models/Actors/Enemy/CodeZero/Head/HeadModel.hpp>

namespace abyss::CodeZero
{
    class CodeZeroActor;
}
namespace abyss::CodeZero::Head
{
    class HeadActor:
        public IActor,
        public Receiver
    {
    public:
        enum State
        {
            Base,
        };
    private:
        Ref<HeadModel> m_head;
        Ref<ParentCtrlModel> m_parent;
    public:
        HeadActor(CodeZeroActor* parent);

        s3d::Vec2 getPos()const;

        CShape getCollider() const;
        bool accept(const ActVisitor& visitor) override;
    };
}