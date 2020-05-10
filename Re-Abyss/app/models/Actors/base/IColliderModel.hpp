#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/types/CShape.hpp>
namespace abyss
{
    class IColliderModel
    {
        IActor* m_pActor;
    protected:
        s3d::String m_tag;
        s3d::String m_layer;
    public:
        IColliderModel(IActor* pActor);
        virtual ~IColliderModel() = default;
        virtual CShape getCollider() const = 0;

        IColliderModel& setTag(const s3d::String& tag);
        const s3d::String& getTag() const;

        IColliderModel& setLayer(const s3d::String& layer);
        const s3d::String& getLayer() const;

        bool isActive() const;

        s3d::uint64 getId() const;
        IActor* getActor() const
        {
            return m_pActor;
        }
        void onReflesh();
        void onCollisionEnter(IActor* col);
        void onCollisionStay(IActor* col);
        void onCollisionExit(IActor* col);
    };
}