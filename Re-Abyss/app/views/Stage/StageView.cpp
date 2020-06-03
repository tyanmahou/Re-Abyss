#include "StageView.hpp"
#include <abyss/controllers/BackGround/BackGround.hpp>
#include <abyss/controllers/Decor/Decor.hpp>
#include <abyss/views/Camera/CameraView.hpp>
#include <abyss/controllers/Manager/Manager.hpp>

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
    void StageView::setup(Manager* pManager)
    {
        m_bubbles.init(pManager->getModule<TimeController>());
    }
    void StageView::setTime(double time)
    {
        m_decor->update(time);
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
        m_bubbles.draw(camera.getCameraPos());
    }
}
