#pragma once
#include <abyss/models/Decor/base/IDecorModel.hpp>

namespace abyss
{
    class CommonDecorModel : public IDecorModel
    { 
        s3d::uint32 m_gId;
        s3d::Quad m_quad;
        bool m_isMirrored = false;
        bool m_isFlipped = false;
    public:
        CommonDecorModel(
            s3d::uint32 gId,
            const s3d::Quad& quad,
            bool isMirrored = false,
            bool isFlipped = false
        );

        s3d::uint32 getGId()const { return m_gId; }
        const s3d::Quad& getQuad()const { return m_quad;}
        bool isMirroed()const { return m_isMirrored; }
        bool isFlipped()const { return m_isFlipped; }

        bool isInScreen(const s3d::RectF& screen)const override;
    };
}