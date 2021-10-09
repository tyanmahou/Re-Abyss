#include "DecorHolder.hpp"
#include <abyss/modules/Decor/base/DecorObj.hpp>
#include <abyss/components/Decor/Common/DecorInfo.hpp>

namespace abyss::Decor
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
            if (obj->isDestroyed()) {
                obj->end();
            } else {
                m_decors.push_back(std::move(obj));
            }
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
        for (auto&& obj : m_decors) {
            obj->end();
        }
        m_decors.clear();
    }

    void DecorHolder::clear(BufferLayer layer)
    {
        auto pred = [layer](const std::shared_ptr<DecorObj>& obj) {
            return obj->getBufferLayer() == layer;
        };
        s3d::Erase_if(m_reserves, pred);

        auto predAndEnd = [pred](const std::shared_ptr<DecorObj>& obj) {
            if (pred(obj)) {
                obj->end();
                return true;
            }
            return false;
        };
        s3d::Erase_if(m_decors, predAndEnd);
    }

    size_t DecorHolder::size() const
    {
        return m_decors.size();
    }
    DeployIds DecorHolder::getDeployIds() const
    {
        DeployIds ret;
        for (auto&& obj : m_reserves) {
            if (auto&& deployId = obj->getDeployId()) {
                ret[*deployId] = obj;
            }
        }
        for (auto&& obj : m_decors) {
            if (auto&& deployId = obj->getDeployId()) {
                ret[*deployId] = obj;
            }
        }
        return ret;
    }
}
