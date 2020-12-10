#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/types/CShape.hpp>
#include <abyss/controllers/Actors/base/IActor.hpp>

namespace abyss::Actor
{
    class ICollider
    {
    protected:
        IActor* m_pActor;
        s3d::String m_layer;

        bool m_isActive = true;
    public:
        ICollider(IActor* pActor);
        virtual ~ICollider() = default;
        virtual CShape getCollider() const = 0;

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

        template<Tag::Tagged T>
        bool isThen(std::function<void(IActor*)> callback) const
        {
            if (m_pActor->getTag().is<T>()) {
                callback(m_pActor);
                return true;
            }
            return false;
        }
        template<Tag::Tagged T, IsComponent C>
        bool isThen(std::function<void(C&)> callback) const
        {
            if (m_pActor->getTag().is<T>()) {
                if (auto c = m_pActor->find<C>()) {
                    callback(*c.get());
                    return true;
                }
            }
            return false;
        }
        template<Tag::Tagged T>
        bool isNotThen(std::function<void(IActor*)> callback) const
        {
            if (m_pActor->getTag().isNot<T>()) {
                callback(m_pActor);
                return true;
            }
            return false;
        }
    };
}