#pragma once
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/controllers/Actors/base/Attacker.hpp>
#include <abyss/controllers/Actors/base/Receiver.hpp>

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
    private:
        Ref<BodyModel> m_body;
        Ref<ScaleModel> m_scale;
    public:
        ShotActor(CodeZeroActor* parent);

        CShape getCollider() const;
        bool accept(const ActVisitor& visitor) override;
    };
}