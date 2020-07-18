#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/models/Actors/base/IComponent.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Schield
{
    class FaceCtrlModel :
        public IComponent
    {
        IActor* m_pActor;
        Ref<BodyModel> m_body;
        bool m_onFace = true;
    public:
        FaceCtrlModel(IActor* pActor);

        void setup() override;

        FaceCtrlModel& on()
        {
            m_onFace = true;
            return *this;
        }
        FaceCtrlModel& off()
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