#include <abyss/views/UI/BossArrival/BossArrivalVM.hpp>
#include <abyss/views/util/Anchor/AnchorUtil.hpp>
#include <abyss/commons/Resource/Font/FontAssetName.hpp>
#include <abyss/params/UI/BossArrival/Param.hpp>

namespace abyss::UI::BossArrival
{
    BossArrivalVM::BossArrivalVM():
        m_font(Param::FontSize, Resource::FontAssetName::PixelMplus12B)
    {
    }
    BossArrivalVM& BossArrivalVM::setPos(const s3d::Vec2& pos)
    {
        m_shader.setPos(pos);
        return *this;
    }
    void BossArrivalVM::draw() const
    {
        // Warning
        {
            constexpr auto* warningText = U"WARNING WARNING WARNING WARNING WARNING WARNING WARNING";
            constexpr double thick = 3;
            double move = -m_timeRate * 50;
            const Vec2 pivot0{ move,Param::Pivot0 };
            const Vec2 pivot1{ move,Param::Pivot1 };
            const double alpha = [this]() {
                if (m_timeRate <= 0.2) {
                    return m_timeRate / 0.2;
                } else if (m_timeRate < 0.9) {
                    return 1.0;
                } else {
                    return 1.0-(m_timeRate-0.9) / 0.1;
                }
            }();

            const ColorF color(1, 0, 0, alpha);
            Line(AnchorUtil::FromTl(pivot0), AnchorUtil::FromTr(pivot0)).draw(thick, color);
            Line(AnchorUtil::FromTl(pivot1), AnchorUtil::FromTr(pivot1)).draw(thick, color);
            m_font(warningText).draw(Arg::leftCenter = (pivot0 + pivot1) /2 , color);
            Line(AnchorUtil::FromBl(pivot0), AnchorUtil::FromBr(pivot0)).draw(thick, color);
            Line(AnchorUtil::FromBl(pivot1), AnchorUtil::FromBr(pivot1)).draw(thick, color);
            m_font(warningText).draw(Arg::rightCenter = AnchorUtil::FromBr((pivot0 + pivot1) / 2), color);
        }
        // Center Text
        {
            auto scoped = m_shader
                .setTime(m_timeRate)
                .start();
            s3d::Graphics2D::DrawTriangles(46 * 2 * 2);
        }
    }
}
