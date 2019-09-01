#pragma once
#include <application/util/Observable.hpp>

#include <memory>
#include <Siv3D/Fwd.hpp>
#include <Siv3D/Array.hpp>
#include <domain/model/object/DoorModel.hpp>
namespace abyss
{
	class WorldObject;
	class PlayerModel;
	class DoorModel;

	class WorldObservable
	{
	protected:
		s3d::Array<std::function<void()>> m_eventTriggers;

	private:
		Observable<void(PlayerModel*, const DoorModel&)> m_onIntoDoor;
		Observable<void(std::shared_ptr<WorldObject>)> m_onCreateObject;
	public:
		inline Observable<void(PlayerModel*, const DoorModel&)>& onIntoDoor()
		{
			return m_onIntoDoor;
		}
		inline void notifyIntoDoor(PlayerModel* player, const DoorModel& door)
		{
			m_eventTriggers.push_back([=]() {m_onIntoDoor.notify(player, door); });
		}

		inline Observable<void(std::shared_ptr<WorldObject>)>& onCreateObject()
		{
			return m_onCreateObject;
		}
		inline void notifyCreateObject(std::shared_ptr<WorldObject> obj)
		{
			m_eventTriggers.push_back([=]() {m_onCreateObject.notify(obj); });
		}
	};
}