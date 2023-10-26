#include <abyss/views/UI/Common/Tips/TipsView.hpp>

#include <abyss/commons/FontName.hpp>
#include <abyss/commons/Constants.hpp>
#include <abyss/params/UI/Common/FooterParam.hpp>
#include <abyss/views/util/Anchor/AnchorUtil.hpp>
#include <Siv3D.hpp>

namespace abyss::UI
{
    void TipsView::DrawFooter(s3d::StringView message, double rate)
    {
        constexpr Color backColor(62, 166, 246, 128);

        RectF(AnchorUtil::FromBl(0, 40), Constants::AppResolutionF.x, 40).draw(backColor);

        auto moveRate = s3d::Min(1.0, rate * 4.0 / 3.0);
        FontAsset(FontName::Tips)(message).draw(Arg::bottomRight = AnchorUtil::FromBr(FooterParam::Tips::BasePos + (1 - moveRate) * Vec2{-20, 0}), ColorF(1, rate));
    }
}
