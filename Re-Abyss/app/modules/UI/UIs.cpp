#include <abyss/modules/UI/UIs.hpp>

namespace abyss::UI
{
    void UIs::flush()
    {
        m_userInterfaces.flush();
    }
    void UIs::update()
    {
        m_userInterfaces.flush();
        m_userInterfaces.update();
        m_userInterfaces.postUpdate();
        m_userInterfaces.erase();
    }
    void UIs::draw() const
    {
        m_userInterfaces.draw();
    }
    Ref<UI::UIObj> UIs::create()
    {
        return this->regist(std::make_shared<UI::UIObj>());
    }
    Ref<UI::UIObj> UIs::regist(const std::shared_ptr<UI::UIObj>& ui)
    {
        ui->setManager(m_pManager);
        m_userInterfaces.push(ui);
        return ui;
    }

    void UIs::setFilter(const Filter& filter)
    {
        m_userInterfaces.setFilter(filter);
    }
    Filter UIs::getFilter() const
    {
        return m_userInterfaces.getFilter();
    }
}
