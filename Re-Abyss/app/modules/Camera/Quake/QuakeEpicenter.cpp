#include <abyss/modules/Camera/Quake/QuakeEpicenter.hpp>
#include <abyss/utils/Interp/InterpUtil.hpp>
#include <Siv3D.hpp>

namespace abyss
{
    QuakeEpicenter::QuakeEpicenter(double maxOffset, double timeSec)
    {
        m_shake.request(maxOffset, timeSec);
    }

    void QuakeEpicenter::update(double dt)
    {
        m_shake.update(dt);
    }
    void QuakeEpicenter::stop()
    {
        m_shake.stop();
    }
    bool QuakeEpicenter::isEnd() const
    {
        return m_shake.isEnd();
    }
    const s3d::Vec2& QuakeEpicenter::getOffset() const
    {
        return m_shake.getShakeOffset();
    }
}
