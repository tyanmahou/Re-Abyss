#pragma once
#include <memory>
#include <functional>

#include <Siv3D/Array.hpp>
#include <abyss/commons/Fwd.hpp>

namespace abyss
{
    class Depends
    {
        class Impl;
        std::shared_ptr<Impl> m_pImpl;
        void addAfter(const std::function<bool(IComponent*)>& f);
        void addBefore(const std::function<bool(IComponent*)>& f);
    public:
        Depends();

        template<class Component>
        void addAfter() const
        {
            addAfter([](IComponent* c) {return dynamic_cast<Component*>(c) != nullptr; });
        }
        template<class Component>
        void addBefore() const
        {
            addBefore([](IComponent* c) {return dynamic_cast<Component*>(c) != nullptr; });
        }

        bool isAfter(IComponent* c) const;
        bool isBefore(IComponent* c) const;
    };
}