#include "DecorBuildUtil.hpp"
#include <abyss/entities/Decor/DecorEntity.hpp>
#include <Siv3D.hpp>

namespace abyss::DecorBuildUtil
{
    s3d::RectF ToRect(const decor::DecorEntity& entity)
    {
        return s3d::RectF{ entity.pos - entity.size / 2.0, entity.size };
    }
    s3d::Quad ToQuad(const decor::DecorEntity& entity)
    {
        RectF rect{ entity.pos - entity.size / 2.0, entity.size };
        return rect.rotatedAt(rect.bl(), s3d::ToRadians(entity.rotation));
    }
    bool IsInScreen(const decor::DecorEntity& entity, const s3d::RectF& screen)
    {
        return ToQuad(entity).intersects(screen);
    }
}
