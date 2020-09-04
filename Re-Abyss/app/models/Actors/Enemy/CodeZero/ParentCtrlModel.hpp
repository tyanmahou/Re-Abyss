#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/models/Actors/base/IComponent.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Actor::CodeZero
{
    class CodeZeroActor;
    class PartsModel;

    class ParentCtrlModel : public IComponent
    {
        IActor* m_parent;
        Ref<HPModel> m_hp;
        Ref<BodyModel> m_body;
        Ref<StateModel> m_state;
        Ref<PartsModel> m_parts;

    public:
        ParentCtrlModel(IActor* parent);

        void setup() override;
        IActor* getParent()const
        {
            return m_parent;
        }

        Ref<HPModel> getHp()const;

        const s3d::Vec2& getPos() const;

        bool isPhase1()const;
        bool isPhase2()const;
        bool isPhase3()const;

        bool isShotCharge()const;
    };
}