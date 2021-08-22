#include "CustomCollider.hpp"

namespace abyss::Actor
{
    void CustomCollider::setup([[maybe_unused]]Executer executer)
    {
        if (m_pImpl) {
            m_pImpl->setup(executer);
        }
    }
    void CustomCollider::onStart()
    {
        if (m_pImpl) {
            m_pImpl->onStart();
        }
    }
    CustomCollider& CustomCollider::setImpl(const std::shared_ptr<IImpl>& impl)
    {
        m_pImpl = impl;
        return *this;
    }
    CustomCollider& CustomCollider::setColFunc(const std::function<CShape()>& func)
    {
        class Impl : public IImpl
        {
            std::function<CShape()> m_colFunc;
        public:

            Impl(const std::function<CShape()>& func) :
                m_colFunc(func)
            {}

            void onStart() override
            {}
            CShape getCollider() const override
            {
                if (m_colFunc) {
                    return m_colFunc();
                }
                return s3d::none;
            }
        };
        m_pImpl = std::make_shared<Impl>(func);
        return *this;
    }

    CShape CustomCollider::getCollider() const
    {
        if (!m_pImpl) {
            return s3d::none;
        }
        if (!m_isActive) {
            return s3d::none;
        }
        return m_pImpl->getCollider();
    }

}
