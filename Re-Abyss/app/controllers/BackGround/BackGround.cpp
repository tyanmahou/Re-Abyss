#include "BackGround.hpp"

namespace abyss
{
    void BackGround::add(const BackGroundVM& backGround)
    {
        m_view.addBackGround(backGround);
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
