#include "TipsView.hpp"
#include <abyss/commons/FontName.hpp>
#include <abyss/params/Cycle/Common/FooterParam.hpp>

#include <Siv3D.hpp>
namespace abyss::Cycle
{
    void TipsView::DrawFooter(s3d::StringView message)
    {
        FontAsset(FontName::Tips)(message).draw(Arg::bottomRight = FooterParam::Tips::BasePos);
    }
}
