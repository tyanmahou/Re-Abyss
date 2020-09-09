#include "CustomDraw.hpp"

namespace abyss::Actor
{
    CustomDraw& CustomDraw::setDrawer(std::unique_ptr<IImpl>&& drawer)
    {
        m_pImpl = std::move(drawer);
        return *this;
    }
    CustomDraw& CustomDraw::setDrawer(const std::function<void()>& drawer)
    {
        class Impl : public IImpl
        {
            std::function<void()> m_drawer;
        public:

            Impl(const std::function<void()>& drawer) :
                m_drawer(drawer)
            {}

            void setup() override
            {}
            void onDraw([[maybe_unused]]const s3d::String& motion) const override
            {
                if (m_drawer) {
                    m_drawer();
                }
            }
        };
        m_pImpl = std::make_unique<Impl>(drawer);
        return *this;
    }
    CustomDraw& CustomDraw::setDrawer(const std::function<void(const s3d::String&)>& drawer)
    {
        class Impl : public IImpl
        {
            std::function<void(const s3d::String&)> m_drawer;
        public:

            Impl(const std::function<void(const s3d::String&)>& drawer):
                m_drawer(drawer)
            {}

            void setup() override
            {
            }
            void onDraw(const s3d::String& motion) const override
            {
                if (m_drawer) {
                    m_drawer(motion);
                }
            }
        };
        m_pImpl = std::make_unique<Impl>(drawer);
        return *this;
    }
    void CustomDraw::setup()
    {
        if (m_pImpl) {
            m_pImpl->setup();
        }
    }
    void CustomDraw::onDraw() const
    {
        if (m_pImpl) {
            m_pImpl->onDraw(m_motion);
        }
    }
}