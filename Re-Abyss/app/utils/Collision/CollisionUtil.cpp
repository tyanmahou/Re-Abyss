#include <abyss/utils/Collision/CollisionUtil.hpp>
#include <Siv3D.hpp>
#include <abyss/utils/Collision/CShape.hpp>
#include <concepts>

namespace
{
    using namespace abyss;

    template<class T, class U>
    concept HasIntersects = requires(T & a, U & b)
    {
        { s3d::Geometry2D::Intersect(a, b) }->std::same_as<bool>;
    };

    bool Intersects(const s3d::Array<CShape>& a, const CShape& b)
    {
        return a.any([&](const CShape& shape) {
            return ColisionUtil::Intersects(shape, b);
        });
    }

    bool Intersects(const CShape& a, const s3d::Array<CShape>& b)
    {
        return Intersects(b, a);
    }
}

namespace abyss
{
    bool ColisionUtil::Intersects(const CShape& a, const CShape& b)
    {
        auto f = [&] <class T, class U>([[maybe_unused]] const T & _a, [[maybe_unused]] const U & _b)
        {
            if constexpr (std::is_same_v<T, s3d::Array<CShape>>) {
                return ::Intersects(_a, b);
            } else if constexpr (std::is_same_v<U, s3d::Array<CShape>>) {
                return ::Intersects(a, _b);
            } else if constexpr (HasIntersects<T, U>) {
                return s3d::Geometry2D::Intersect(_a, _b);
            } else {
                return false;
            }
        };
        return std::visit(f, a, b);
    }
}
