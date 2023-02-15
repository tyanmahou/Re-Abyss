#include <abyss/components/Actor/Common/BossFadeHider.hpp>
#include <abyss/components/Actor/Common/BossFadeMask.hpp>

#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/modules/Sfx/SpecialEffects.hpp>

namespace abyss::Actor
{
    BossFadeHider::BossFadeHider(ActorObj* pActor) :
        m_pActor(pActor)
    {
    }
    void BossFadeHider::setup(Executer executer)
    {
        executer.onStart().addAfter<BossFadeMask>();
    }
    void BossFadeHider::onStart()
    {
        m_fadeMask = m_pActor->find<BossFadeMask>();
    }
    void BossFadeHider::onPreDraw()
    {
        if (!m_fadeMask) {
            return;
        }
        auto* bossFade = m_pActor->getModule<SpecialEffects>()->bossFade();
        if (!bossFade->isActive()) {
            return;
        }
        m_fadeMask->setRate(bossFade->getFadeInRate());
    }
}
