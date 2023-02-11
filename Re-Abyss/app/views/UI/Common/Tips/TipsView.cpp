#include <abyss/views/UI/Common/Tips/TipsView.hpp>

#include <abyss/commons/FontName.hpp>
#include <abyss/params/UI/Common/FooterParam.hpp>
#include <abyss/views/util/Anchor/AnchorUtil.hpp>
#include <Siv3D.hpp>

namespace abyss::UI
{
    void TipsView::DrawFooter(s3d::StringView message)
    {
        FontAsset(FontName::Tips)(message).draw(Arg::bottomRight = AnchorUtil::FromBr(FooterParam::Tips::BasePos));
    }
}
