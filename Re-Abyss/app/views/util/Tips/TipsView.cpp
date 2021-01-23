#include "TipsView.hpp"
#include <abyss/commons/FontName.hpp>
#include <Siv3D.hpp>
namespace abyss::Tips
{
    void TipsView::DrawFooter(s3d::StringView message)
    {
        FontAsset(FontName::Tips)(message).draw(Arg::bottomRight = Vec2{950, 500});
    }
}
