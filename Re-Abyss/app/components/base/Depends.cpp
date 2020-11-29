#include "Depends.hpp"

namespace abyss
{
    class Depends::Impl
    {
        s3d::Array<std::function<bool(IComponent*)>> m_after;
        s3d::Array<std::function<bool(IComponent*)>> m_before;
    public:
        Impl() = default;

        void addAfter(const std::function<bool(IComponent*)>& f)
        {
            m_after.push_back(f);
        }
        void addBefore(const std::function<bool(IComponent*)>& f)
        {
            m_before.push_back(f);
        }
        bool isAfter(IComponent* c) const
        {
            for (auto& f : m_after) {
                if (f(c)) {
                    return true;
                }
            }
            return false;
        }
        bool isBefore(IComponent* c) const
        {
            for (auto& f : m_before) {
                if (f(c)) {
                    return true;
                }
            }
            return false;
        }
    };

    Depends::Depends():
        m_pImpl(std::make_shared<Impl>())
    {}
    void Depends::addAfter(const std::function<bool(IComponent*)>& f)
    {
        m_pImpl->addAfter(f);
    }
    void Depends::addBefore(const std::function<bool(IComponent*)>& f)
    {
        m_pImpl->addBefore(f);
    }
    bool Depends::isAfter(IComponent * c) const
    {
        return m_pImpl->isAfter(c);
    }
    bool Depends::isBefore(IComponent* c) const
    {
        return m_pImpl->isBefore(c);
    }
}
