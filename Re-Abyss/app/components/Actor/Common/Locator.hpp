#pragma once
#include <abyss/components/base/IComponent.hpp>

#include <abyss/components/Actor/Common/ILocator.hpp>
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

        const s3d::Vec2& getPos() const
        {
            return m_pos;
        }

        s3d::Vec2 getCenterPos() const override
        {
            return this->getPos();
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