#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/models/Actors/base/IComponent.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::CodeZero
{
    class CodeZeroActor;

    class ParentCtrlModel : public IComponent
    {
        CodeZeroActor* m_parent;
        Ref<HPModel> m_hp;
        Ref<StateModel> m_state;
    public:
        ParentCtrlModel(CodeZeroActor* parent);

        void setup() override;
        CodeZeroActor* getParent()const
        {
            return m_parent;
        }

        Ref<HPModel> getHp()const;

        const s3d::Vec2& getPos() const;

        bool isPhase1()const;
        bool isPhase2()const;
        bool isPhase3()const;
    };
}