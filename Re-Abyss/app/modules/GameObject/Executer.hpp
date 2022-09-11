#pragma once
#include <memory>
#include <functional>
#include <typeindex>

#include <Siv3D/Array.hpp>
#include <abyss/commons/Fwd.hpp>

namespace abyss
{
    class Executer
    {
        class Command
        {
            const Executer* m_executer;
            std::type_index m_process;
            void addAfter(const std::function<bool(IComponent*)>& f) const;
            void addBefore(const std::function<bool(IComponent*)>& f) const;
        public:
            Command(const Executer* executer, const std::type_index& process);

            template<class Component = IComponent>
            void addAfter() const
            {
                addAfter([](IComponent* c) {return dynamic_cast<Component*>(c) != nullptr; });
            }
            template<class Component = IComponent>
            void addBefore() const
            {
                addBefore([](IComponent* c) {return dynamic_cast<Component*>(c) != nullptr; });
            }
            bool isAfter(IComponent* c) const;
            bool isBefore(IComponent* c) const;
        };

    public:
        Executer();

        Command on(const std::type_index& process) const;

        template<class Process>
        Command on() const
        {
            return this->on(typeid(Process));
        }

        Command onStart() const;

        [[deprecated("Unimplemented")]]
        Command onEnd() const;
    private:
        class Impl;
        std::shared_ptr<Impl> m_pImpl;
    };
}
