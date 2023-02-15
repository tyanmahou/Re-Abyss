#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Actor::Enemy::CodeZero
{
    class CodeZeroActor;
    class PartsCtrl;

    class ParentCtrl : public IComponent
    {
        ActorObj* m_parent;
        Ref<HP> m_hp;
        Ref<Body> m_body;
        Ref<StateCtrl> m_state;
        Ref<PartsCtrl> m_parts;

    public:
        ParentCtrl(ActorObj* parent);

        void onStart() override;
        ActorObj* getParent()const
        {
            return m_parent;
        }

        Ref<HP> getHp()const;

        const s3d::Vec2& getPos() const;

        bool isShotCharge()const;

        bool isExistParent()const;
    };
}
