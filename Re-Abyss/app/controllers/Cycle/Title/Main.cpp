#include "Main.hpp"
#include <abyss/commons/InputManager/InputManager.hpp>

namespace abyss::Cycle::Title
{
    Main::Main(IMainObserver* observer) :
        m_observer(observer)
    {}

    Main::~Main()
    {}

    void Main::update()
    {

    }

    void Main::draw() const
    {
    }
}
