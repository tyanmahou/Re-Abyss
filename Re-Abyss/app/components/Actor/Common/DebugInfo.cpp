#include "DebugInfo.hpp"
#if ABYSS_DEBUG 
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/debugs/Debug.hpp>
#include <Siv3D.hpp>

namespace abyss::Actor
{
	DebugInfo::DebugInfo(ActorObj* pActor):
		m_pActor(pActor)
	{
	}
	void DebugInfo::onStart()
	{
		m_worldComment = m_pActor->getModule<WorldComment>()->getRequestor();
		m_hp = m_pActor->find<HP>();
		m_body = m_pActor->find<Body>();
	}
	void DebugInfo::onPreDraw()
	{
		if (!Debug::Menu::IsDebug(Debug::DebugFlag::ActorDebugInfo)) {
			return;
		}
		if (!m_body) {
			return;
		}
		String text;
		if (m_hp) {
			text += U"HP: {}/{}"_fmt(m_hp->getHp(), m_hp->getMaxHp());
		}
		m_worldComment->comment(text, m_body->region().topCenter());
	}
}
#endif