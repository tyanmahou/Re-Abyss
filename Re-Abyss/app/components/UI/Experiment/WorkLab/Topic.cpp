#include <abyss/components/UI/Experiment/WorkLab/Topic.hpp>
#if ABYSS_DEVELOP

namespace abyss::UI::Experiment::WorkLab
{
    Topic::Topic():
       m_timer(3.0s, StartImmediately::No)
    {
    }
    void Topic::update()
    {
        if (KeyZ.down()) {
            m_timer.restart();
        }
    }
    void Topic::draw() const
    {
        auto scoped = m_shader
            .setTime(m_timer.progress0_1())
            .start();
        s3d::Graphics2D::DrawTriangles(46 * 2 * 2);
    }
}
#endif
