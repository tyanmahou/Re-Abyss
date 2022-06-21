#include <abyss/utils/Layout/Window/detail/Component.hpp>

#include <abyss/utils/Layout/Window/detail/GrabCtrl.hpp>
#include <abyss/utils/Layout/Window/detail/ScrollCtrl.hpp>
#include <abyss/utils/Layout/Window/detail/WindowMover.hpp>
#include <abyss/utils/Layout/Window/detail/WindowResizer.hpp>

namespace abyss::Layout::Window::detail
{
    Component::Component(WindowParam& param) :
        m_param(param),
        m_grabCtrl(std::make_unique<GrabCtrl>(this)),
        m_resizer(std::make_unique<WindowResizer>(this)),
        m_scrollCtrl(std::make_unique<ScrollCtrl>(this)),
        m_mover(std::make_unique<WindowMover>(this))
    {
    }
    Component::~Component()
    {
    }
}
