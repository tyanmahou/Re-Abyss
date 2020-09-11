#pragma once
#include <Siv3D/Fwd.hpp>
#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Actor
{

    class Terrain;

    /// <summary>
    /// 地形判定処理
    /// </summary>
    class IPhysics
    {
    protected:
        IActor* m_pActor;
        bool m_isActive = true;
    public:
        IPhysics(IActor* p):
            m_pActor(p)
        {}
        virtual ~IPhysics() = default;

        IActor* getActor() const
        {
            return m_pActor;
        }

        IPhysics& setActive(bool isActive)
        {
            m_isActive = isActive;
            return *this;
        }
        bool isActive() const;

        virtual s3d::RectF getCollider() const = 0;

        virtual void onCollision(const Ref<Actor::Terrain>& terrain) = 0;

        bool intersects(const MapColInfo& mapColInfo) const;
    };
}