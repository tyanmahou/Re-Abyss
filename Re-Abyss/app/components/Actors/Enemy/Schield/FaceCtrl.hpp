#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/base/IComponent.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Actor::Enemy::Schield
{
    class FaceCtrl :
        public IComponent
    {
        IActor* m_pActor;
        Ref<BodyModel> m_body;
        bool m_onFace = true;
    public:
        FaceCtrl(IActor* pActor);

        void setup() override;

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