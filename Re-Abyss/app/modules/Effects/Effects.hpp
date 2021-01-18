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

        void init(const GlobalTime& time);

        template<EffectGroup Group>
        void add(std::unique_ptr<s3d::IEffect>&& effect) const
        {
            m_effects[static_cast<size_t>(Group)].add(std::move(effect));
        }

        template<EffectGroup Group, class Type, class... Args>
        void add(Args&& ... args) const
        {
            m_effects[static_cast<size_t>(Group)].add<Type>(std::forward<Args>(args)...);
        }

        void addWorldBack(std::unique_ptr<s3d::IEffect>&& effect) const
        {
            this->add<EffectGroup::WorldBack>(std::move(effect));
        }

        template<class Type, class... Args>
        void addWorldBack(Args&& ... args) const
        {
            this->add<EffectGroup::WorldBack, Type>(std::forward<Args>(args)...);
        }

        void addWorldFront(std::unique_ptr<s3d::IEffect>&& effect) const
        {
            this->add<EffectGroup::WorldFront>(std::move(effect));
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

        template<EffectGroup Group>
        size_t num() const
        {
            return m_effects[static_cast<size_t>(Group)].num_effects();
        }
    };
}