#pragma once
#include <abyss/models/Actors/base/IComponent.hpp>
#include <abyss/commons/Fwd.hpp>
namespace abyss
{
    class ICollisionCallbackModel : virtual public IComponent
    {
    protected:
        bool m_isActive = true;
    public:
        bool setActive(bool isActive)
        {
            m_isActive = isActive;
        }
        bool isActive() const
        {
            return m_isActive;
        }
        virtual void onReflesh(){}
        virtual void onCollisionEnter(IActor*) {}
        virtual void onCollisionStay(IActor*) {}
        virtual void onCollisionExit(IActor*) {}
    };
}