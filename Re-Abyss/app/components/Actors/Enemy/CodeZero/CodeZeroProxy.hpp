#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Actors/Commons/Body.hpp>
#include <abyss/components/Actors/Enemy/CodeZero/PartsCtrl.hpp>

namespace abyss::Actor::Enemy::CodeZero
{
    class CodeZeroProxy:
        public IComponent
    {
    public:
        CodeZeroProxy(IActor* pActor);

        void onStart() override;
        void setActive(bool isActive);

        const s3d::Vec2& getPos()const;
        IActor* getActor() const
        {
            return m_pActor;
        }
    private:
        IActor* m_pActor;
        Ref<Actor::Body> m_body;
        Ref<PartsCtrl> m_parts;
    };
}