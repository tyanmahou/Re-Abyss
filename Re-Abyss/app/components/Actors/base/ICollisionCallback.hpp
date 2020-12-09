#pragma once
#include <abyss/commons/Fwd.hpp>
namespace abyss::Actor
{
    class ICollider;

    class ICollisionCallback
    {
    protected:
        bool m_isActive = true;
    public:
        virtual ~ICollisionCallback() = default;
        bool setActive(bool isActive)
        {
            m_isActive = isActive;
        }
        bool isActive() const
        {
            return m_isActive;
        }
        virtual void onReflesh(){}
        virtual void onCollisionEnter(ICollider*) {}
        virtual void onCollisionStay(ICollider*) {}
        virtual void onCollisionExit(ICollider*) {}
    };
}