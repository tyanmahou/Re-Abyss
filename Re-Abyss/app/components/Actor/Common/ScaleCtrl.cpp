#include <abyss/components/Actor/Common/ScaleCtrl.hpp>

namespace abyss::Actor
{
    ScaleCtrl::ScaleCtrl(double initScale) :
        m_scale(initScale),
        m_minScale(s3d::none),
        m_maxScale(s3d::none)
    {}
    ScaleCtrl& ScaleCtrl::setTo(double scale, double timeSec)
    {
        double diff = scale - m_scale;
        if (diff > 0) {
            m_maxScale = scale;
        } else if (diff < 0) {
            m_minScale = scale;
        }
        if (timeSec <= 0.0) {
            m_rate = 0;
            m_scale = scale;
        } else {
            m_rate = diff / timeSec;
        }
        return *this;
    }
    ScaleCtrl& ScaleCtrl::setTo(double init, double to, double timeSec)
    {
        m_scale = init;
        return this->setTo(to, timeSec);
    }
    ScaleCtrl& ScaleCtrl::setToImmediate(double scale)
    {
        m_rate = 0;
        m_scale = scale;
        m_minScale = m_maxScale = s3d::none;
        return *this;
    }
    void ScaleCtrl::update(double dt)
    {
        m_scale += m_rate * dt;
        
        m_minScale.then([this](double min) {
            if (m_scale < min) {
                m_scale = min;
            }
        });
        m_maxScale.then([this](double max) {
            if (m_scale > max) {
                m_scale = max;
            }
        });
    }
}
