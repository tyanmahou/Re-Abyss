#pragma once
#include <abyss/models/Actors/base/IComponent.hpp>
#include <abyss/commons/Fwd.hpp>
#include <abyss/types/CShape.hpp>
namespace abyss
{
    class IColliderModel : public IComponent
    {
        IActor* m_pActor;
    protected:
        s3d::String m_tag;
        s3d::String m_layer;
    public:
        IColliderModel(IActor* pActor);

        virtual CShape getCollider() const = 0;

        void setTag(const s3d::String& tag);
        const s3d::String& getTag() const;

        void setLayer(const s3d::String& layer);
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