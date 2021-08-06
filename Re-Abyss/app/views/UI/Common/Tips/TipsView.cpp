#include "TipsView.hpp"
#include <abyss/commons/FontName.hpp>
#include <abyss/params/UI/Common/FooterParam.hpp>
#include <abyss/views/util/Pivot/PivotUtil.hpp>
#include <Siv3D.hpp>
namespace abyss::UI
{
    void TipsView::DrawFooter(s3d::StringView message)
    {
        FontAsset(FontName::Tips)(message).draw(Arg::bottomRight = PivotUtil::FromBr(FooterParam::Tips::BasePos));
    }
}
