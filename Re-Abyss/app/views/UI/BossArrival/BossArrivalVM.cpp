#include <abyss/views/UI/BossArrival/BossArrivalVM.hpp>
#include <abyss/views/util/Anchor/AnchorUtil.hpp>
namespace abyss::UI::BossArrival
{
    BossArrivalVM::BossArrivalVM()
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
            constexpr double thick = 3;
            constexpr Vec2 pivot0{ 0,90 };
            constexpr Vec2 pivot1{ 0,150 };
            constexpr Vec2 axis{ 1, -1 };
            double alpha = 1.0;

            const ColorF color(1, 0, 0, alpha);
            Line(AnchorUtil::FromTl(pivot0), AnchorUtil::FromTr(pivot0)).draw(thick, color);
            Line(AnchorUtil::FromTl(pivot1), AnchorUtil::FromTr(pivot1)).draw(thick, color);
            Line(AnchorUtil::FromBl(pivot0 * axis), AnchorUtil::FromBr(pivot0 * axis)).draw(thick, color);
            Line(AnchorUtil::FromBl(pivot1 * axis), AnchorUtil::FromBr(pivot1 * axis)).draw(thick, color);
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
