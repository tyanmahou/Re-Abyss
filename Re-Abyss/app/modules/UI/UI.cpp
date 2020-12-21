#include "UI.hpp"

namespace abyss
{
    void UI::flush()
    {
        m_userInterfaces.flush();
    }
    void UI::update(double dt)
    {
        m_userInterfaces.update(dt);
        m_userInterfaces.erase();
    }
    void UI::draw() const
    {
        m_userInterfaces.draw();
    }
    void UI::regist(const std::shared_ptr<ui::IUserInterface>& ui)
    {
        ui->setManager(m_pManager);
        m_userInterfaces.push(ui);
    }

    void UI::setActiveAll(bool isActive)
    {
        m_userInterfaces.setActiveAll(isActive);
    }

}
