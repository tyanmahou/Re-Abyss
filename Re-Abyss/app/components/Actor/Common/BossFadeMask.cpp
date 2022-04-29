#include <abyss/components/Actor/Common/BossFadeMask.hpp>

#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/modules/Sfx/SpecialEffects.hpp>

namespace abyss::Actor
{
    BossFadeMask::BossFadeMask(ActorObj* pActor):
        m_pActor(pActor)
    {
    }
    void BossFadeMask::setup(Executer executer)
    {
        if (m_drawer) {
            m_drawer->setup(executer);
        }
    }
    void BossFadeMask::onStart()
    {
        if (m_drawer) {
            m_drawer->onStart();
        }
    }

    void BossFadeMask::onDraw() const
    {
        auto* bossFade = m_pActor->getModule<SpecialEffects>()->bossFade();
        if (!bossFade->isActive()) {
            return;
        }
        {
            auto recordBegin = bossFade->record();
            if (m_drawer) {
                m_drawer->onDraw();
            }
        }
    }
    DrawLayer BossFadeMask::getLayer() const
    {
        if (m_drawer) {
            return m_drawer->getLayer();
        }
        return DrawLayer::World;
    }
    double BossFadeMask::getOrder() const
    {
        if (m_drawer) {
            return m_drawer->getOrder();
        }
        return 0.0;
    }

    //-----------------------------------
    BossFadeMaskFromMainVModel::BossFadeMaskFromMainVModel(ActorObj* pActor):
        m_pActor(pActor)
    {}
    void BossFadeMaskFromMainVModel::setup(Executer executer)
    {
        executer.on<IDraw>().addAfter<VModel>();
    }
    void BossFadeMaskFromMainVModel::onStart()
    {
        m_view = m_pActor->find<VModel>();
    }
    void BossFadeMaskFromMainVModel::onDraw() const
    {
        m_view->onDraw();
    }
    DrawLayer BossFadeMaskFromMainVModel::getLayer() const
    {
        return m_view->getLayer();
    }
    double BossFadeMaskFromMainVModel::getOrder() const
    {
        return m_view->getOrder();
    }
}
