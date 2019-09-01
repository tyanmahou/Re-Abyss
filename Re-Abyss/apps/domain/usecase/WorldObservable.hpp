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
	class SlimeModel;
	class PlayerShotModel;

	class WorldObservable
	{
		template<class T>
		using CreateNotify = Observable<void(const std::shared_ptr<T>&)>;
	protected:
		s3d::Array<std::function<void()>> m_eventTriggers;

#define OnCreateObject(Type)\
    private:\
		CreateNotify<Type> m_onCreate##Type;\
    public:\
		inline void subscribe(CreateNotify<Type>::value_type callback)\
		{\
			m_onCreate##Type.subscribe(callback);\
		}\
		inline void notifyCreateWorldObject(const std::shared_ptr<Type>& obj)\
		{\
            m_eventTriggers.push_back([=](){m_onCreate##Type.notify(obj);});\
		}

		OnCreateObject(WorldObject)
		OnCreateObject(PlayerModel)
		OnCreateObject(PlayerShotModel)
		OnCreateObject(SlimeModel)
#undef OnCreateObject

	private:
		Observable<void(PlayerModel*, const DoorModel&)> m_onIntoDoor;

	public:
		inline Observable<void(PlayerModel*, const DoorModel&)>& onIntoDoor()
		{
			return m_onIntoDoor;
		}
		inline void notifyIntoDoor(PlayerModel* player, const DoorModel& door)
		{
			m_eventTriggers.push_back([=]() {m_onIntoDoor.notify(player, door); });
		}
	};
}