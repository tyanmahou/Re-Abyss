#pragma once
#include <Siv3D/Fwd.hpp>
#include <abyss/commons/Fwd.hpp>

namespace abyss
{
    class IPhysicsModel
    {
        IActor* m_pActor;
    protected:
        bool m_isActive = true;
    public:
        IPhysicsModel(IActor* pActor);
        virtual ~IPhysicsModel() = default;
        virtual s3d::RectF getCollider() const = 0;

        IPhysicsModel& setActive(bool isActive);
        bool isActive() const;

        IActor* getActor() const
        {
            return m_pActor;
        }
        void onCollision(IActor* col);
    };
}