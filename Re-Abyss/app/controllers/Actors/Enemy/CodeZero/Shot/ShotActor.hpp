#pragma once
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/controllers/Actors/base/Attacker.hpp>
#include <abyss/controllers/Actors/base/Receiver.hpp>

#include <abyss/models/Actors/base/StateModel.hpp>
#include <abyss/models/Actors/CodeZero/ParentCtrlModel.hpp>
#include <abyss/models/Actors/Commons/BodyModel.hpp>
#include <abyss/models/Actors/Commons/ScaleModel.hpp>

namespace abyss::CodeZero
{
    class CodeZeroActor;
}
namespace abyss::CodeZero::Shot
{
    class ShotVM;

    class ShotActor: 
        public IActor,
        public Attacker,
        public Receiver
    {
    public:
        enum State
        {
            Wait,
            Pursuit,
            PursuitEnd,
        };
    private:
        Ref<BodyModel> m_body;
        Ref<ScaleModel> m_scale;
        std::shared_ptr<ShotVM> m_view;
    public:
        ShotActor(CodeZeroActor* parent);

        CShape getCollider() const;
        bool accept(const ActVisitor& visitor) override;

        ShotVM* getBindedView()const;
    };
}