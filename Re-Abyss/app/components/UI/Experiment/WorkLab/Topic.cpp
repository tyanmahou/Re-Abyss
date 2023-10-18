#include <abyss/components/UI/Experiment/WorkLab/Topic.hpp>
#if ABYSS_DEVELOP

namespace abyss::UI::Experiment::WorkLab
{
    Topic::Topic()
    {
    }
    void Topic::update()
    {
    }
    void Topic::draw() const
    {
        auto scoped = m_shader.start();
        s3d::Graphics2D::DrawTriangles(46 * 2);
    }
}
#endif
