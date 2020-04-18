#pragma once
#include <abyss/models/Decor/base/IDecorModel.hpp>

namespace abyss
{
    class MapDecorModel : public IDecorModel
    {
        s3d::uint32 m_gId;
        s3d::RectF m_rect;
    public:
        MapDecorModel(
            s3d::uint32 gId,
            const s3d::RectF& rect
        );
        s3d::uint32 getGId()const { return m_gId; }
        const s3d::RectF& region()const { return m_rect; }
        bool isInScreen(const s3d::RectF& screen) const override;
    };
}