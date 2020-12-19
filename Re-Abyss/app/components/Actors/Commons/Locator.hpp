#pragma once
#include <abyss/components/base/IComponent.hpp>

#include <abyss/components/Actors/base/ILocator.hpp>
namespace abyss::Actor
{
    class Locator : 
        public IComponent,
        public ILocator
    {
        s3d::Vec2 m_pos;
    public:
        Locator() = default;

        Locator& setPos(const s3d::Vec2& pos)
        {
            m_pos = pos;
            return *this;
        }

        const s3d::Vec2& getPos() const override
        {
            return m_pos;
        }
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::Locator>
    {
        using Base = Actor::ILocator;
    };
}