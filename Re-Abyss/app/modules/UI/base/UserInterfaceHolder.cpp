#include "UserInterfaceHolder.hpp"
namespace abyss::ui
{
    void UserInterfaceHolder::flush()
    {
        if (m_reserves.empty()) {
            return;
        }
        // startでregistされてもいいようにここでmove
        auto registing = std::move(m_reserves);
        m_reserves.clear();
        for (auto& obj : registing) {
            obj->start();
            m_uis.push_back(std::move(obj));
        }
        m_uis.sort_by([](const std::shared_ptr<IUserInterface>& a, const std::shared_ptr<IUserInterface>& b) {
            return a->getOrder() < b->getOrder();
        });
    }

    void UserInterfaceHolder::push(const std::shared_ptr<IUserInterface> & ui)
    {
        m_reserves.push_back(ui);
    }

    void UserInterfaceHolder::update(double dt)
    {
        this->flush();
        for (auto& obj : m_uis) {
            if (!obj->isActive()) {
                continue;
            }
            obj->update(dt);
        }
    }

    void UserInterfaceHolder::draw() const
    {
        for (auto& obj : m_uis) {
            if (!obj->isActive()) {
                continue;
            }
            obj->draw();
        }
    }

    void UserInterfaceHolder::erase()
    {
        s3d::Erase_if(m_uis, [](const std::shared_ptr<IUserInterface>& obj) {
            return obj->isDestroyed();
        });
    }

    void UserInterfaceHolder::clear()
    {
        m_reserves.clear();
        m_uis.clear();
    }

    void UserInterfaceHolder::setActiveAll(bool isActive)
    {
        for (auto&& ui : m_reserves) {
            ui->setActive(isActive);
        }
        for (auto&& ui : m_uis) {
            ui->setActive(isActive);
        }
    }

}
