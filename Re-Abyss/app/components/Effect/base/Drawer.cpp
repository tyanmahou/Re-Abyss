#include "Drawer.hpp"
#include <abyss/modules/Effect/base/EffectObj.hpp>
#include <abyss/components/Effect/base/IDraw.hpp>
#include <abyss/modules/DrawManager/DrawManager.hpp>

namespace abyss::Effect
{
    Drawer::Drawer(EffectObj* pObj) :
        m_pObj(pObj)
    {}
    void Drawer::onStart()
    {
        auto draws = m_pObj->finds<IDraw>();
        m_drawTasks.reserve(draws.size());
        for (auto&& com : draws) {
            m_drawTasks.push_back([](EffectObj* pObj, Ref<IDraw> com)->Coro::Task<> {
                auto* drawManager = pObj->getModule<DrawManager>();
                bool isEnd = false;
                while (!isEnd) {
                    if (!com) {
                        break;
                    }
                    drawManager->add(pObj->getLayer(), [=, &isEnd] {
                        if (!com->onDraw(pObj->drawTimeSec())) {
                            isEnd = true;
                        }
                    });
                    co_yield{};
                }
                co_return;
            }(m_pObj, std::move(com)));
        }
    }
    void Drawer::draw() const
    {
        bool isActive = false;
        for (auto& t : m_drawTasks) {
            isActive |= t.moveNext();
        }
        if (!isActive) {
            m_pObj->destroy();
        }
    }
}