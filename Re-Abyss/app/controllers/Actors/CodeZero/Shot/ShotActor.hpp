#pragma once
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/controllers/Actors/base/Attacker.hpp>
#include <abyss/controllers/Actors/base/Receiver.hpp>
#include <abyss/controllers/Actors/base/IState.hpp>

#include <abyss/models/Actors/Commons/BodyModel.hpp>
#include <abyss/models/Actors/Commons/ScaleModel.hpp>

namespace abyss
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
        CodeZeroActor* m_parent;
        BodyModel m_body;
        ScaleModel m_scale;

        StateManager<ShotActor> m_state;
        std::shared_ptr<ShotVM> m_view;
    public:
        ShotActor(CodeZeroActor* parent);

        void update(double dt) override;
        void lastUpdate(double dt) override;
        void draw() const override;

        CShape getCollider() const override;
        bool accept(const ActVisitor& visitor) override;

        ShotVM* getBindedView()const;
    };
}