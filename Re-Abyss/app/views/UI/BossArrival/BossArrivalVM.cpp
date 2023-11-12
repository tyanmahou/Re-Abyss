#include <abyss/views/UI/BossArrival/BossArrivalVM.hpp>
#include <abyss/views/util/Anchor/AnchorUtil.hpp>
#include <abyss/commons/Constants.hpp>
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
        Vec2 pos = m_shader.getPos();
        // Warning
        {
            const double alpha = [this]() {
                if (m_timeRate <= 0.2) {
                    return m_timeRate / 0.2;
                } else if (m_timeRate < 0.9) {
                    return 1.0;
                } else {
                    return 1.0-(m_timeRate-0.9) / 0.1;
                }
            }();
            {
                const double radiusRate = [this]() {
                    if (m_timeRate <= 0.9) {
                        return 0.95 + 0.05 * m_timeRate / 0.9;
                    } else {
                        return s3d::EaseInCirc(1 - (m_timeRate -0.9) / 0.1);
                    }
                }();
                const Vec2 center = Constants::AppResolution / 2 + pos;
                const double radius0 = radiusRate * 250;
                const double startAngle = ToRadians(20);
                const double angle = ToRadians(140);
                const double radius1 = radiusRate * 400;
                const double thickHalf0 = 15;
                const double thickHalf1 = 5;
                const ColorF color(1, 0, 0, alpha * 0.4);
                Circle(center, radius0).drawArc(m_timeRate + startAngle, angle, thickHalf0, thickHalf0, color);
                Circle(center, radius0).drawArc(m_timeRate - startAngle, -angle, thickHalf0, thickHalf0, color);
                Circle(center, radius1).drawArc(-m_timeRate + startAngle + Math::HalfPi, angle, thickHalf1, thickHalf1, color);
                Circle(center, radius1).drawArc(-m_timeRate - startAngle + Math::HalfPi, -angle, thickHalf1, thickHalf1, color);
            }
            {
                constexpr auto* warningText = U"WARNING WARNING WARNING WARNING WARNING WARNING WARNING";
                constexpr double thick = 3;
                double move = -m_timeRate * 50;
                const Vec2 pivot0{ move,Param::Pivot0 };
                const Vec2 pivot1{ move,Param::Pivot1 };
                const ColorF color(1, 0, 0, alpha);

                Line(pos+ AnchorUtil::FromTl(pivot0), pos + AnchorUtil::FromTr(pivot0)).draw(thick, color);
                Line(pos+ AnchorUtil::FromTl(pivot1), pos + AnchorUtil::FromTr(pivot1)).draw(thick, color);
                m_font(warningText).draw(Arg::leftCenter = pos + (pivot0 + pivot1) / 2, color);
                Line(pos + AnchorUtil::FromBl(pivot0), pos + AnchorUtil::FromBr(pivot0)).draw(thick, color);
                Line(pos + AnchorUtil::FromBl(pivot1), pos + AnchorUtil::FromBr(pivot1)).draw(thick, color);
                m_font(warningText).draw(Arg::rightCenter = pos + AnchorUtil::FromBr((pivot0 + pivot1) / 2), color);
            }
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
