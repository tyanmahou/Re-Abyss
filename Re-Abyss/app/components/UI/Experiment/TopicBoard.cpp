#include <abyss/components/UI/Experiment/TopicBoard.hpp>
#if ABYSS_DEVELOP
#include <abyss/commons/Constants.hpp>
#include <abyss/modules/UI/base/UIObj.hpp>
#include <abyss/components/UI/Experiment/Main.hpp>

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
        m_list = std::make_unique<List::SimpleVerticalList>();
    }
    TopicBoard::~TopicBoard()
    {
    }
    void TopicBoard::setup(Executer executer)
    {
        executer.on<IDraw>().addAfter<Main>();
    }
    void TopicBoard::onStart()
    {
        m_main = m_pUi->find<Main>();
        for (auto&& topic : m_topics) {
            m_list->push_back({
                .title = topic.title,
                .onClick = [this, factory = topic.factory] {
                    m_main->setTopic(factory());
                },
                .backGroundColor = ColorF(0.5, 1),
            });
        }
    }
    void TopicBoard::onDraw() const
    {
        m_window->draw([this](const s3d::RectF screen) {
            m_list->setScreen(screen)
                .setFontColor(s3d::Palette::White)
                .draw();
        });
    }
}
#endif
