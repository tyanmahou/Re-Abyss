#pragma once
#include <Siv3D/Fwd.hpp>
#include <abyss/commons/Fwd.hpp>

namespace abyss::ui
{
    class IUserInterface
    {
    private:
        bool m_isDestroyed = false;
    protected:
        bool m_isActive = true;
        Manager* m_pManager = nullptr;
        s3d::int32 m_order = 0;
    public:
        virtual ~IUserInterface() = default;

        void setManager(Manager* const pManager)
        {
            m_pManager = pManager;
        }
        void setActive(bool active)
        {
            m_isActive = active;
        }
        bool isActive() const
        {
            return m_isActive;
        }
        void destroy()
        {
            m_isDestroyed = true;
        }
        bool isDestroyed() const
        {
            return m_isDestroyed;
        }

        s3d::int32 getOrder() const
        {
            return m_order;
        }
        virtual void start() {}
        virtual void update([[maybe_unused]]double dt) {}
        virtual void draw() const = 0;
    };
}