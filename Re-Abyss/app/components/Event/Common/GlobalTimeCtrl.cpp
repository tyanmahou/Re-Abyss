#include "GlobalTimeCtrl.hpp"
#include <abyss/modules/GlobalTime/GlobalTime.hpp>
#include <abyss/modules/Event/base/IEvent.hpp>

#include <abyss/components/Event/base/IGlobalTimeScale.hpp>

namespace abyss::Event
{
    GlobalTimeCtrl::GlobalTimeCtrl(IEvent* pEvent):
        m_pEvent(pEvent),
        m_timeScaleModel(std::make_shared<GlobalTimeScaleModel>())
    {}
    void GlobalTimeCtrl::onStart()
    {
        auto globalTime = m_pEvent->getModule<GlobalTime>();
        globalTime->addTimeScale(m_timeScaleModel);
    }
    void GlobalTimeCtrl::onLastUpdate()
    {
        double totalScale = 1.0f;
        for (const auto& globalTimeScale : m_pEvent->finds<IGlobalTimeScale>()) {
            totalScale *= globalTimeScale->getGlobalTimeScale();
        }
        m_timeScaleModel->setScale(totalScale);
    }
}
