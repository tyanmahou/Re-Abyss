#include "CommonDecorModel.hpp"

namespace abyss
{
    CommonDecorModel::CommonDecorModel(
        s3d::uint32 gId, 
        const s3d::Quad& quad,
        bool isMirrored,
        bool isFlipped
    ):
        m_gId(gId),
        m_quad(quad),
        m_isMirrored(isMirrored),
        m_isFlipped(isFlipped)
    {}

    bool CommonDecorModel::isInScreen(const s3d::RectF & screen) const
    {
        return screen.intersects(m_quad);
    }

}
