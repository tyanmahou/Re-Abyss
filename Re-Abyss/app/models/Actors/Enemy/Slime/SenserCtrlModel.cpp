#include "SenserCtrlModel.hpp"
#include <abyss/controllers/Actors/Enemy/Slime/SlimeActor.hpp>
#include <abyss/controllers/Actors/Enemy/Slime/Senser/SenserActor.hpp>
#include <abyss/controllers/World/World.hpp>

namespace abyss::Slime
{
    SenserCtrlModel::SenserCtrlModel(SlimeActor* pActor):
        m_pActor(pActor)
    {}
    void SenserCtrlModel::onStart()
    {
        m_senser = m_pActor->getModule<World>()->create<SenserActor>(m_pActor);
    }

    void SenserCtrlModel::destroy()
    {
        if (m_senser) {
            m_senser->destroy();
        }
    }

}
