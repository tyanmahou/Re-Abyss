#pragma once

#include <abyss/utils/EffectEx/EffectEx.hpp>

namespace abyss
{
    class WorldView
    {
    private:
        EffectEx m_effect;
    public:
        template<class Type, class... Args>
        void addEffect(Args&& ... args)
        {
            m_effect.add<Type>(std::forward<Args>(args)...);
        }
        void draw() const;
    };
}
