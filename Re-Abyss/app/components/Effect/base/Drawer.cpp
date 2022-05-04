#include <abyss/components/Effect/base/Drawer.hpp>

#include <abyss/modules/Effect/base/EffectObj.hpp>
#include <abyss/components/Effect/base/IDrawParts.hpp>
#include <abyss/modules/DrawManager/DrawManager.hpp>

namespace abyss::Effect
{
    Drawer::Drawer(EffectObj* pObj) :
        m_pObj(pObj)
    {}
    void Drawer::onStart()
    {
        auto draws = m_pObj->finds<IDrawParts>();
        m_drawTasks.reserve(draws.size());
        for (auto&& com : draws) {
            m_drawTasks.push_back([](EffectObj* pObj, Drawer* drawer, Ref<IDrawParts> com)->Coro::Task<> {
                auto* drawManager = pObj->getModule<DrawManager>();
                bool isEnd = false;
                while (!isEnd) {
                    if (!com) {
                        break;
                    }
                    drawManager->add(drawer->getLayer(), [=, &isEnd] {
                        if (!com->onDraw(pObj->timeSec())) {
                            isEnd = true;
                        }
                    }, drawer->getOrder());
                    co_yield{};
                }
                co_return;
            }(m_pObj, this, std::move(com)));
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
