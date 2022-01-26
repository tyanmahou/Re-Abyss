#include <abyss/components/Actor/Common/VModelUpdater.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>

namespace abyss::Actor
{
	VModelUpdater::VModelUpdater(ActorObj* pActor):
		m_pActor(pActor)
	{
	}
	void VModelUpdater::onPreDraw()
	{
		m_time += m_timeScale * m_pActor->deltaTime();
	}
}
