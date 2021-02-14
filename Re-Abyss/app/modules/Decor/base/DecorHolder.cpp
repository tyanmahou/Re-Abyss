#include "DecorHolder.hpp"
#include <abyss/modules/Decor/base/DecorObj.hpp>

namespace abyss::decor
{
    void DecorHolder::flush()
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
            m_decors.push_back(std::move(obj));
        }
    }

    void DecorHolder::push(const std::shared_ptr<DecorObj>&decor)
    {
        m_reserves.push_back(decor);
    }

    void DecorHolder::update()
    {
        for (auto& obj : m_decors) {
            if (!obj->isActive()) {
                continue;
            }
            obj->update();
        }
    }

    void DecorHolder::draw() const
    {
        for (auto& obj : m_decors) {
            if (!obj->isActive()) {
                continue;
            }
            obj->draw();
        }
    }

    void DecorHolder::erase()
    {
        s3d::Erase_if(m_decors, [](const std::shared_ptr<DecorObj>& obj) {
            if (obj->isDestroyed()) {
                obj->end();
                return true;
            }
            return false;
        });
    }

    void DecorHolder::clear()
    {
        m_reserves.clear();
        for (auto&& ui : m_decors) {
            ui->end();
        }
        m_decors.clear();
    }

}