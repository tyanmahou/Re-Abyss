#pragma once
#include <abyss/commons/Fwd.hpp>

namespace abyss
{
    class ColisionUtil
    {
    private:
        ColisionUtil() = default;
    public:
        static [[nodiscard]] bool Intersects(const CShape& a, const CShape& b);
    };
}