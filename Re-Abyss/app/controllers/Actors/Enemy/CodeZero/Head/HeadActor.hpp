#pragma once
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/controllers/Actors/base/Receiver.hpp>
#include <abyss/types/Forward.hpp>
#include <abyss/models/Actors/base/StateModel.hpp>
#include <abyss/models/Actors/CodeZero/ParentCtrlModel.hpp>
#include <abyss/models/Actors/CodeZero/Head/HeadModel.hpp>

namespace abyss::CodeZero
{
    class CodeZeroActor;
}
namespace abyss::CodeZero::Head
{
    class HeadVM;

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

        std::shared_ptr<HeadVM> m_view;
    public:
        HeadActor(CodeZeroActor* parent);

        s3d::Vec2 getPos()const;

        CShape getCollider() const;
        bool accept(const ActVisitor& visitor) override;

        HeadVM* getBindedView()const;
    };
}