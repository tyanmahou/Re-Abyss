#pragma once

#include <Siv3D/Effect.hpp>

namespace abyss
{
    class WorldView
    {
    private:
        s3d::Effect m_effect;
    public:
        template<class Type, class... Args>
        void addEffect(Args&& ... args)
        {
            m_effect.add<Type>(std::forward<Args>(args)...);
        }
        void draw() const;
    };
}
