#include "UI.hpp"

namespace abyss
{
    void UI::flush()
    {
        m_userInterfaces.flush();
    }
    void UI::update()
    {
        m_userInterfaces.update();
        m_userInterfaces.erase();
    }
    void UI::draw() const
    {
        m_userInterfaces.draw();
    }
    Ref<ui::IUserInterface> UI::create()
    {
        return this->regist(std::make_shared<ui::IUserInterface>());
    }
    Ref<ui::IUserInterface> UI::regist(const std::shared_ptr<ui::IUserInterface>& ui)
    {
        ui->setManager(m_pManager);
        m_userInterfaces.push(ui);
        return ui;
    }

    void UI::setActiveAll(bool isActive)
    {
        m_userInterfaces.setActiveAll(isActive);
    }

}
