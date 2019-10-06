#pragma once
#include <application/util/Observable.hpp>

#include <memory>
#include <Siv3D/Fwd.hpp>
#include <Siv3D/Array.hpp>
#include <domain/actor/DoorActor.hpp>

#include <domain/visitor/ViewVisitor.hpp>

namespace abyss
{
	class IActor;
	class PlayerActor;
	class DoorActor;

	class WorldObservable
	{
	protected:
		s3d::Array<std::function<void()>> m_eventTriggers;

	private:
		Observable<void(PlayerActor*, const DoorActor&)> m_onIntoDoor;
		ViewVisitor m_onCreateObject;
	public:
		inline Observable<void(PlayerActor*, const DoorActor&)>& onIntoDoor()
		{
			return m_onIntoDoor;
		}
		inline void notifyIntoDoor(PlayerActor* player, const DoorActor& door)
		{
			m_eventTriggers.push_back([=]() {m_onIntoDoor.notify(player, door); });
		}

		inline void subsucrimeCreateObject(ViewVisitor&& visiter)
		{
			m_onCreateObject = std::move(visiter);
		}
		template<class T>
		inline void notifyCreateObject(const std::shared_ptr<T>& obj)
		{
			m_eventTriggers.push_back([=]() {m_onCreateObject.visit(obj); });
		}
	};
}