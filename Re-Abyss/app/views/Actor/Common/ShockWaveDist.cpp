#include "ShockWaveDist.hpp"
#include <abyss/modules/Manager/Manager.hpp>
#include <abyss/modules/Camera/Camera.hpp>
#include <abyss/modules/Camera/Distortion/Distortion.hpp>

#include <Siv3D.hpp>

namespace abyss
{
    ShockWaveDist::ShockWaveDist(Manager* pManager, const s3d::Vec2& pos, double radius, double power, double timeScale):
        m_pManager(pManager),
        m_pos(pos),
        m_radius(radius),
        m_power(power),
        m_timeScale(timeScale)
    {}

    bool ShockWaveDist::update(double t)
    {
        t *= m_timeScale;
        double rate = EaseOut(Easing::Quint, t);
        auto distortion = m_pManager->getModule<Camera>()->getDistortion();

        distortion->addCircleFrame(
            Circle(m_pos, m_radius * rate),
            10,
            10,
            0,
            s3d::Math::Lerp(0.0, m_power, s3d::Periodic::Triangle0_1(1s, rate))
        );
        return t <= 1.0f;
    }
}
