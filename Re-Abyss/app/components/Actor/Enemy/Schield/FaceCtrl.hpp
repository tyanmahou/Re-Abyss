#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Actor::Enemy::Schield
{
    class FaceCtrl :
        public IComponent
    {
        ActorObj* m_pActor;
        Ref<Body> m_body;
        bool m_onFace = true;
    public:
        FaceCtrl(ActorObj* pActor);

        void onStart() override;

        FaceCtrl& on()
        {
            m_onFace = true;
            return *this;
        }
        FaceCtrl& off()
        {
            m_onFace = false;
            return *this;
        }
        bool isOnFace()const
        {
            return m_onFace;
        }
        s3d::Circle getCollider() const;
    };
}