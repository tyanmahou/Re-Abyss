#include "CustomColliderModel.hpp"

namespace abyss::Actor
{
    void CustomColliderModel::setup()
    {
        if (m_pImpl) {
            m_pImpl->setup();
        }
    }
    CustomColliderModel& CustomColliderModel::setImpl(std::unique_ptr<IImpl>&& impl)
    {
        m_pImpl = std::move(impl);
        return *this;
    }
    CustomColliderModel& CustomColliderModel::setColFunc(const std::function<CShape()>& func)
    {
        class Impl : public IImpl
        {
            std::function<CShape()> m_colFunc;
        public:

            Impl(const std::function<CShape()>& func) :
                m_colFunc(func)
            {}

            void setup() override
            {}
            CShape getCollider() const override
            {
                if (m_colFunc) {
                    return m_colFunc();
                }
                return s3d::none;
            }
        };
        m_pImpl = std::make_unique<Impl>(func);
        return *this;
    }

    CShape CustomColliderModel::getCollider() const
    {
        if (!m_pImpl) {
            return s3d::none;
        }
        return m_pImpl->getCollider();
    }

}
