#pragma once
#include <Siv3D/Fwd.hpp>
#include <abyss/commons/Fwd.hpp>
#include <abyss/types/CShape.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Actor
{
    /// <summary>
    /// あたり判定処理
    /// </summary>
    class ICollision
    {
    protected:
        IActor* m_pActor;
        bool m_isActive = true;

        s3d::int32 m_layer;
    public:
        ICollision(IActor* p) :
            m_pActor(p)
        {}
        virtual ~ICollision() = default;

        IActor* getActor() const
        {
            return m_pActor;
        }

        ICollision& setActive(bool isActive)
        {
            m_isActive = isActive;
            return *this;
        }
        bool isActive() const;

        ICollision& setLayer(s3d::int32 layer);
        s3d::int32 getLayer() const;

        s3d::uint64 getId() const;

        virtual CShape getCollider() const = 0;

        virtual void onCollision(const Ref<ICollision>& other) = 0;

        bool intersects(const CShape& other) const;
    };
}