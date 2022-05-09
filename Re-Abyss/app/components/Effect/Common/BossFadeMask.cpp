#include <abyss/components/Effect/Common/BossFadeMask.hpp>
#include <abyss/modules/Effect/base/EffectObj.hpp>
#include <abyss/modules/Sfx/SpecialEffects.hpp>
#include <Siv3D.hpp>

namespace abyss::Effect
{
	BossFadeMask::BossFadeMask(EffectObj* pObj):
		m_pObj(pObj)
	{}
    void BossFadeMask::onStart()
    {
		m_drawer = m_pObj->find<Drawer>();
    }
	DrawLayer BossFadeMask::getLayer() const
	{
		return m_drawer->getLayer();
	}
	double BossFadeMask::getOrder() const
	{
		return m_drawer->getOrder();
	}

	void BossFadeMask::onDraw() const
	{
        auto* bossFade = m_pObj->getModule<SpecialEffects>()->bossFade();
        if (!bossFade->isActive()) {
            return;
        }
        {
            static BlendState blend{
                true,
                Blend::Zero,
                Blend::Zero,
                BlendOp::Add,
                Blend::One,
                Blend::One,
                BlendOp::Max
            };
            ScopedRenderStates2D state(blend);
            auto recordBegin = bossFade->record();
            if (m_drawer) {
                m_drawer->onDraw();
            }
        }
	}
}