#include "DecorBuildUtil.hpp"
#include <abyss/commons/Constants.hpp>
#include <abyss/entities/Decor/DecorEntity.hpp>
#include <Siv3D.hpp>

namespace abyss::DecorBuildUtil
{
    s3d::RectF ToRect(const Decor::DecorEntity& entity)
    {
        return s3d::RectF{ entity.pos - entity.size / 2.0, entity.size };
    }
    s3d::RectF ToBoundRect(const Decor::DecorEntity& entity)
    {
        s3d::Quad quad = ToQuad(entity);
        Vec2 min = quad.p0;
        Vec2 max = quad.p0;
        for (size_t index = 1; index < 4; ++index) {
            auto& pos = quad.p(index);

            if (min.x > pos.x) {
                min.x = pos.x;
            } else if (max.x < pos.x) {
                max.x = pos.x;
            }

            if (min.y > pos.y) {
                min.y = pos.y;
            } else if (max.y < pos.y) {
                max.y = pos.y;
            }
        }
        return RectF(min, max - min);
    }
    s3d::Quad ToQuad(const Decor::DecorEntity& entity)
    {
        RectF rect{ entity.pos - entity.size / 2.0, entity.size };
        return rect.rotatedAt(rect.bl(), s3d::ToRadians(entity.rotation));
    }
    s3d::Quad ToQuad(const s3d::Vec2& pos, const Decor::DecorEntity& entity)
    {
        RectF rect{ pos - entity.size / 2.0, entity.size };
        return rect.rotatedAt(rect.bl(), s3d::ToRadians(entity.rotation));
    }
    bool IsInScreen(const Decor::DecorEntity& entity, const s3d::RectF& screen)
    {
        auto tl = screen.tl();
        auto br = screen.br();

        // パララックス係数の適用
        auto ptl = entity.pos + tl - tl * entity.parallax;
        auto pbr = entity.pos + br - br * entity.parallax;
        if (ptl.x > pbr.x) {
            std::swap(ptl.x, pbr.x);
        }
        if (ptl.y > pbr.y) {
            std::swap(ptl.y, pbr.y);
        }

        // バウンド
        auto boundSizeHalf = ToBoundRect(entity).size / 2.0;
        auto bptl = ptl - boundSizeHalf;
        auto bpbr = pbr + boundSizeHalf;
        return RectF(bptl, bpbr - bptl).intersects(screen);
    }
}
