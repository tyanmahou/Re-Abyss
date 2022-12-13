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
        m_drawFibers.reserve(draws.size());
        for (auto&& com : draws) {
            m_drawFibers.push_back([](EffectObj* pObj, Ref<IDrawParts> com)->Coro::Fiber<> {
                while (true) {
                    if (!com) {
                        break;
                    }
                    if (!com->onDraw(pObj->timeSec())) {
                        break;
                    }
                    co_yield{};
                }
                co_return;
            }(m_pObj, std::move(com)));
        }
    }
    void Drawer::onDraw() const
    {
        bool isActive = false;
        for (auto& t : m_drawFibers) {
            isActive |= t.resume();
        }
        if (!isActive) {
            m_pObj->destroy();
        }
    }
}
