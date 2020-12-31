#include "Executer.hpp"
#include <Siv3D/HashTable.hpp>

namespace abyss
{
    class Executer::Impl
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

    Executer::Command::Command(const Executer* executer, const std::type_index& process):
        m_executer(executer),
        m_process(process)
    {}

    void Executer::Command::addAfter(const std::function<bool(IComponent*)>& f) const
    {
        m_executer->m_pImpl->addAfter(m_process, f);
    }
    void Executer::Command::addBefore(const std::function<bool(IComponent*)>& f) const
    {
        m_executer->m_pImpl->addBefore(m_process, f);
    }
    bool Executer::Command::isAfter(IComponent* c) const
    {
        return m_executer->m_pImpl->isAfter(m_process, c);
    }
    bool Executer::Command::isBefore(IComponent* c) const
    {
        return m_executer->m_pImpl->isBefore(m_process, c);
    }

    Executer::Executer():
        m_pImpl(std::make_shared<Impl>())
    {}
    Executer::Command Executer::on(const std::type_index& process) const
    {
        return Executer::Command(this, process);
    }
}
