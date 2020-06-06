#pragma once
#include <array>
#include <abyss/utils/EffectEx/EffectEx.hpp>
#include <abyss/commons/Fwd.hpp>

namespace abyss
{
    enum class EffectGroup : size_t
    {
        DecorBack,
        WorldBack,
        WorldFront,
        DecorFront,
        Max,
        Bubble = DecorFront,
    };
    class Effects
    {
        std::array<EffectEx, static_cast<size_t>(EffectGroup::Max)> m_effects;

    public:
        Effects();

        void init(const TimeController& time);
        template<EffectGroup Group, class Type, class... Args>
        void add(Args&& ... args) const
        {
            m_effects[static_cast<size_t>(Group)].add<Type>(std::forward<Args>(args)...);
        }

        template<class Type, class... Args>
        void addWorldBack(Args&& ... args) const
        {
            this->add<EffectGroup::WorldBack, Type>(std::forward<Args>(args)...);
        }
        template<class Type, class... Args>
        void addWorldFront(Args&& ... args) const
        {
            this->add<EffectGroup::WorldFront, Type>(std::forward<Args>(args)...);
        }

        template<EffectGroup Group>
        void update() const
        {
            m_effects[static_cast<size_t>(Group)].update();
        }
    };
}