#include "StageView.hpp"
#include <abyss/controllers/BackGround/BackGround.hpp>
#include <abyss/controllers/Decor/Decor.hpp>
#include <abyss/views/Camera/CameraView.hpp>

namespace abyss
{
    StageView& StageView::setDecor(Decor* decor)
    {
        m_decor = decor;
        return *this;
    }
    StageView& StageView::setBg(BackGround* bg)
    {
        m_bg = bg;
        return *this;
    }
    void StageView::drawBack(const CameraView& camera) const
    {
        m_bg->draw(camera);
        m_decor->draw(DecorOrder::Back, camera.screenRegion());
    }
    void StageView::drawMiddle(const CameraView& camera) const
    {
        m_decor->draw(DecorOrder::Middle, camera.screenRegion());
    }
    void StageView::drawFront(const CameraView & camera) const
    {
        m_decor->draw(DecorOrder::Front, camera.screenRegion());
    }
}
