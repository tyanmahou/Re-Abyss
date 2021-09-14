#pragma once
#include <Siv3D/Fwd.hpp>
#include <Siv3D/Optional.hpp>
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
        ActorObj* m_pActor;
        bool m_isActive = true;

        s3d::int32 m_layer;
        s3d::Optional<s3d::int32> m_toLayer;
    public:
        ICollision(ActorObj* p) :
            m_pActor(p)
        {}
        virtual ~ICollision() = default;

        ActorObj* getActor() const
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

        ICollision& setToLayer(s3d::None_t none);
        ICollision& setToLayer(s3d::int32 toLayer);
        s3d::int32 getToLayer() const;

        s3d::uint64 getId() const;

        virtual CShape getCollider() const = 0;

        virtual void onCollision(const Ref<ICollision>& other) = 0;

        bool intersects(const CShape& other) const;
    };
}