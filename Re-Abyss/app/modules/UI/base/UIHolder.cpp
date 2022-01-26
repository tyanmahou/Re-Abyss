#include <abyss/modules/UI/base/UIHolder.hpp>

namespace abyss::UI
{
    void UIHolder::flush()
    {
        if (m_reserves.empty()) {
            return;
        }
        // startでregistされてもいいようにここでmove
        auto registing = std::move(m_reserves);
        m_reserves.clear();
        for (auto& obj : registing) {
            obj->setup();
            obj->start();
            if (obj->isDestroyed()) {
                obj->end();
            } else {
                m_uis.push_back(std::move(obj));
            }
        }
    }

    void UIHolder::push(const std::shared_ptr<UIObj> & ui)
    {
        m_reserves.push_back(ui);
    }

    void UIHolder::update()
    {
        for (auto& obj : m_uis) {
            if (!obj->isActive(m_filter)) {
                continue;
            }
            obj->update();
        }
    }

    void UIHolder::postUpdate()
    {
        for (auto& obj : m_uis) {
            if (!obj->isActive(m_filter)) {
                continue;
            }
            obj->postUpdate();
        }
    }

    void UIHolder::draw() const
    {
        for (auto& obj : m_uis) {
            if (!obj->isActive(m_filter)) {
                continue;
            }
            obj->draw();
        }
    }

    void UIHolder::erase()
    {
        s3d::Erase_if(m_uis, [](const std::shared_ptr<UIObj>& obj) {
            if (obj->isDestroyed()) {
                obj->end();
                return true;
            }
            return false;
        });
    }

    void UIHolder::clear()
    {
        m_reserves.clear();
        for (auto&& ui : m_uis) {
            ui->end();
        }
        m_uis.clear();
    }
}
