#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/base/IComponent.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Actor::Enemy::CodeZero
{
    class CodeZeroActor;
    class PartsCtrl;

    class ParentCtrl : public IComponent
    {
        IActor* m_parent;
        Ref<HP> m_hp;
        Ref<BodyModel> m_body;
        Ref<StateModel> m_state;
        Ref<PartsCtrl> m_parts;

    public:
        ParentCtrl(IActor* parent);

        void setup() override;
        IActor* getParent()const
        {
            return m_parent;
        }

        Ref<HP> getHp()const;

        const s3d::Vec2& getPos() const;

        bool isPhase1()const;
        bool isPhase2()const;
        bool isPhase3()const;

        bool isShotCharge()const;
    };
}