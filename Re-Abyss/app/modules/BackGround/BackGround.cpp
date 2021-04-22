#include "BackGround.hpp"

namespace abyss
{
    void BackGround::update(double time)
    {
        m_view.setTime(time);
        m_waterSarface.setTime(time);
    }
    void BackGround::add(const BackGroundVM& backGround)
    {
        m_view.addBackGround(backGround);
    }
    void BackGround::setBgColor(const s3d::ColorF& color)
    {
        m_view.setBgColor(color);
    }
    const s3d::ColorF& BackGround::getBgColor() const
    {
        return m_view.getBgColor();
    }
    void BackGround::draw(const CameraView& camera) const
    {
        m_view.draw(camera);
    }
    void BackGround::drawWaterSarfaceBack(const CameraView& camera) const
    {
        m_waterSarface.drawBack(camera);
    }
    void BackGround::drawWaterSarfaceFront(const CameraView & camera) const
    {
        m_waterSarface.drawFront(camera);
    }
}
