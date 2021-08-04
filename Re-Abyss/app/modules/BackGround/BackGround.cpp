#include "BackGround.hpp"
#include <abyss/views/Camera/CameraView.hpp>

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
}
