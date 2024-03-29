#include <abyss/views/Distortion/DistortionView.hpp>

#include <abyss/commons/Constants.hpp>
#include <abyss/views/Distortion/DistUtl.hpp>
#include <Siv3D.hpp>

namespace abyss
{
    DistortionView::DistortionView() :
        m_rt(Constants::GameScreenSize_v<int32>.asPoint())
    {
        m_shader.setDistTexture(m_rt);
    }
    void DistortionView::clear()
    {
        m_drawer.clear();
    }

    void DistortionView::addCircle(const s3d::Circle& circle, double power)
    {
        m_drawer.push_back([=] {
            DistUtil::Draw(circle, power);
        });
    }

    void DistortionView::addCircle(const s3d::Circle & circle, double innerPower, double outerPower)
    {
        m_drawer.push_back([=] {
            DistUtil::Draw(circle, innerPower, outerPower);
        });
    }

    void DistortionView::addCircleFrame(const s3d::Circle& circle, double thickness, double power)
    {
        m_drawer.push_back([=] {
            DistUtil::DrawFrame(circle, thickness, power);
        });
    }

    void DistortionView::addCircleFrame(const s3d::Circle& circle, double innerThickness, double outerThickness, double innerPower, double outerPower)
    {    
        m_drawer.push_back([=] {
            DistUtil::DrawFrame(circle, innerThickness, outerThickness, innerPower, outerPower);
        });
    }

    void DistortionView::addCircleFrameGiza(
        const s3d::Circle& circle,
        double innerThickness,
        double outerThickness,
        double innerSpread,
        double outerSpread,
        double innerPower,
        double outerPower,
        double rotate,
        double quality
        )
    {
        m_drawer.push_back([=] {
            DistUtil::DrawFrameGiza(circle, innerThickness, outerThickness, innerSpread, outerSpread, innerPower, outerPower, rotate, quality);
        });
    }

    void DistortionView::render() const
    {
        ScopedRenderTarget2D target(m_rt);
        m_rt.clear(ColorF(0.5, 0.5, 0.0, 1.0));
        ScopedRenderStates2D blend(BlendState(
            true,
            Blend::SrcAlpha,
            Blend::SrcAlpha
        ));
        for (auto&& drawer : m_drawer) {
            drawer();
        }
    }

    s3d::ScopedCustomShader2D DistortionView::start() const
    {
        return m_shader.start();
    }
}
