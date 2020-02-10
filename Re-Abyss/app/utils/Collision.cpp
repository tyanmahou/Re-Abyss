#include "Collision.hpp"

#include <Siv3D.hpp>

#include <abyss/types/CShape.hpp>

namespace
{
    template<class T, class U>
    concept HasIntersects = requires(T & a, U & b)
    {
        { s3d::Geometry2D::Intersect(a, b) }->bool;
    };
}

namespace abyss
{
    bool Intersects(const CShape& a, const CShape& b)
    {
        return std::visit([]<class T, class U>([[maybe_unused]] const T & a, [[maybe_unused]] const U & b)
        {
            if constexpr (HasIntersects<T, U>) {
                return s3d::Geometry2D::Intersect(a, b);
            } else {
                return false;
            }
        }, a, b);
    }
}