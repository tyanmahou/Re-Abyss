#include "Depends.hpp"
#include <Siv3D/HashTable.hpp>

namespace abyss
{
    class Depends::Impl
    {
        struct Edge
        {
            s3d::Array<std::function<bool(IComponent*)>> after{};
            s3d::Array<std::function<bool(IComponent*)>> before{};
        };
        s3d::HashTable<std::type_index, Edge> m_edges;
    public:
        Impl() = default;

        void addAfter(const std::type_index& process, const std::function<bool(IComponent*)>& f)
        {
            m_edges[process].after.push_back(f);
        }
        void addBefore(const std::type_index& process, const std::function<bool(IComponent*)>& f)
        {
            m_edges[process].before.push_back(f);
        }
        bool isAfter(const std::type_index& process, IComponent* c)
        {
            for (auto& f : m_edges[process].after) {
                if (f(c)) {
                    return true;
                }
            }
            return false;
        }
        bool isBefore(const std::type_index& process, IComponent* c)
        {
            for (auto& f : m_edges[process].before) {
                if (f(c)) {
                    return true;
                }
            }
            return false;
        }
    };

    Depends::Command::Command(const Depends* depends, const std::type_index& process):
        m_depends(depends),
        m_process(process)
    {}

    void Depends::Command::addAfter(const std::function<bool(IComponent*)>& f) const
    {
        m_depends->m_pImpl->addAfter(m_process, f);
    }
    void Depends::Command::addBefore(const std::function<bool(IComponent*)>& f) const
    {
        m_depends->m_pImpl->addBefore(m_process, f);
    }
    bool Depends::Command::isAfter(IComponent* c) const
    {
        return m_depends->m_pImpl->isAfter(m_process, c);
    }
    bool Depends::Command::isBefore(IComponent* c) const
    {
        return m_depends->m_pImpl->isBefore(m_process, c);
    }

    Depends::Depends():
        m_pImpl(std::make_shared<Impl>())
    {}
    Depends::Command Depends::on(const std::type_index& process) const
    {
        return Depends::Command(this, process);
    }
}
