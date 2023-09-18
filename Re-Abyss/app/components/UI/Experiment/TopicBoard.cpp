#include <abyss/components/UI/Experiment/TopicBoard.hpp>
#if ABYSS_DEVELOP
#include <abyss/commons/Constants.hpp>
#include "TopicBoard.hpp"

namespace abyss::UI::Experiment
{
    TopicBoard::TopicBoard(UIObj* pUi):
        m_pUi(pUi)
    {
        auto windowContext =
            Layout::Window::WindowContext{ Vec2{Constants::AppResolutionF.x - 400 - 10 , 10}, Vec2{400, 600} }
            .setBackGroundColor(ColorF(0.5, 0.5))
            .setFrameColor(s3d::Palette::White)
            .setScrollBarColor(ColorF(0, 0.5))
            .setScrollGripColor(ColorF(0.9))
            .setCanResize(true)
            .setIsResizeClampSceneSize(false)
            ;
        m_window = std::make_unique<Layout::Window::Window>(windowContext);
    }
    TopicBoard::~TopicBoard()
    {
    }
    void TopicBoard::onDraw() const
    {
    }
}
#endif
