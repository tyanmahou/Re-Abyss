#include "CustomDrawModel.hpp"

namespace abyss
{
    CustomDrawModel& CustomDrawModel::setDrawer(std::unique_ptr<IImpl>&& drawer)
    {
        m_pImpl = std::move(drawer);
        return *this;
    }
    CustomDrawModel& CustomDrawModel::setDrawer(const std::function<void()>& drawer)
    {
        class LambdaImpl : public IImpl
        {
            std::function<void()> m_drawer;
        public:

            LambdaImpl(const std::function<void()>& drawer) :
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
        m_pImpl = std::make_unique<LambdaImpl>(drawer);
        return *this;
    }
    CustomDrawModel& CustomDrawModel::setDrawer(const std::function<void(const s3d::String&)>& drawer)
    {
        class LambdaImpl : public IImpl
        {
            std::function<void(const s3d::String&)> m_drawer;
        public:

            LambdaImpl(const std::function<void(const s3d::String&)>& drawer):
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
        m_pImpl = std::make_unique<LambdaImpl>(drawer);
        return *this;
    }
    void CustomDrawModel::setup()
    {
        if (m_pImpl) {
            m_pImpl->setup();
        }
    }
    void CustomDrawModel::onDraw() const
    {
        if (m_pImpl) {
            m_pImpl->onDraw(m_motion);
        }
    }
}