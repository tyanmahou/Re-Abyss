#include <abyss/components/Effect/Actor/Item/Recovery/Main.hpp>
#include <abyss/modules/Effect/base/EffectObj.hpp>
#include <Siv3D.hpp>

namespace abyss::Effect::Actor::Item::Recovery
{
    Main::Main(EffectObj* pObj, const Ref<abyss::Actor::ILocator>& locator) :
        m_pObj(pObj)
    {}

    Main::~Main()
    {}

    bool Main::onDraw(double time)
    {
        return time <= 1;
    }
}