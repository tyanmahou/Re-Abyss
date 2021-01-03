#if ABYSS_DEBUG
#include "DebugUtil.hpp"
#include <abyss/types/CShape.hpp>
#include <abyss/utils/Overloaded.hpp>

#include <Siv3D.hpp>

namespace abyss::Debug::DebugUtil
{
    void DrawShape(const CShape& shape, const s3d::ColorF& color)
    {
        std::visit(overloaded{
            [&color](const auto& c) {
                c.draw(color);
            },
            [&color](const Vec2& c) {
                Shape2D::Cross(5, 2, c).draw(color);
            },
            [&color](const Array<CShape>& c) {
                for (const auto& shape : c) {
                    DrawShape(shape, color);
                }
            },
            []([[maybe_unused]] const None_t&) {}
        }, shape);
    }
}

#endif
