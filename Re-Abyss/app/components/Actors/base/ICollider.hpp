#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/types/CShape.hpp>
#include <abyss/components/Actors/Commons/Collision/Tag.hpp>

namespace abyss::Actor
{
    class ICollider
    {
    protected:
        IActor* m_pActor;
        Collision::TagType m_tag;
        s3d::String m_layer;

        bool m_isActive = true;
    public:
        ICollider(IActor* pActor);
        virtual ~ICollider() = default;
        virtual CShape getCollider() const = 0;

        ICollider& setTag(Collision::TagType tag);
        const Collision::TagType& getTag() const;

        ICollider& setLayer(const s3d::String& layer);
        const s3d::String& getLayer() const;

        ICollider& setActive(bool isActive);
        bool isActive() const;

        s3d::uint64 getId() const;
        IActor* getActor() const
        {
            return m_pActor;
        }
        void onReflesh();
        void onCollisionEnter(ICollider* col);
        void onCollisionStay(ICollider* col);
        void onCollisionExit(ICollider* col);

        template<Collision::Tag::Tagged T>
        bool isThen(std::function<void(IActor*)> callback) const
        {
            if (m_tag.is<T>()) {
                callback(m_pActor);
                return true;
            }
            return false;
        }
        template<Collision::Tag::Tagged T>
        bool isNotThen(std::function<void(IActor*)> callback) const
        {
            if (m_tag.isNot<T>()) {
                callback(m_pActor);
                return true;
            }
            return false;
        }
    };
}