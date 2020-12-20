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

            void onStart() override
            {}
            void onDraw() const override
            {
                if (m_drawer) {
                    m_drawer();
                }
            }
        };
        m_pImpl = std::make_unique<Impl>(drawer);
        return *this;
    }

    void CustomDraw::setup([[maybe_unused]]Depends depends)
    {
    }
    void CustomDraw::onStart()
    {
        if (m_pImpl) {
            m_pImpl->onStart();
        }
    }
    void CustomDraw::onDraw() const
    {
        if (m_pImpl) {
            m_pImpl->onDraw();
        }
    }
}