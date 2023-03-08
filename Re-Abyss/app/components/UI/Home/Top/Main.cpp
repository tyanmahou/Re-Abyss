#include <abyss/components/UI/Home/Top/Main.hpp>
#include <abyss/views/UI/Home/Top/TopView.hpp>
#include <Siv3D.hpp>

namespace abyss::UI::Home::Top
{
    Main::Main(UIObj* pUi):
        m_pUi(pUi),
        m_view(std::make_unique<TopView>())
    {}
    Main::~Main()
    {

    }
    void Main::onUpdate()
    {

    }
    void Main::onDraw() const
    {
        m_view->draw();
    }
}
