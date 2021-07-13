#include "Main.hpp"
#include <abyss/commons/Constants.hpp>
#include <Siv3D.hpp>

namespace abyss::UI::Header
{
    Main::Main(UIObj* pUi):
        m_pUi(pUi)
    {}
    void Main::onStart()
    {

    }

    void Main::onDraw() const
    {
        constexpr RectF blackBand{ 0, 0, Constants::GameScreenSize.x, Constants::GameScreenOffset.y };
        blackBand.draw(Palette::Black);
    }
}