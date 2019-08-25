#pragma once
#include <application/util/Observable.hpp>

#include <memory>
#include <Siv3D/Fwd.hpp>

namespace abyss
{
	class WorldObject;
	class PlayerModel;
	class DoorModel;
	class PlayerShotModel;

	class WorldObservable
	{
		template<class T>
		using CreateNotify = Observable<void(const std::shared_ptr<T>&)>;

#define OnCreateObject(Type)\
    private:\
		CreateNotify<Type> m_onCreate##Type;\
    public:\
		inline void subscribe(CreateNotify<Type>::value_type callback)\
		{\
			m_onCreate##Type.subscribe(callback);\
		}\
		inline void onCreateWorldObject(const std::shared_ptr<Type>& obj)\
		{\
            m_onCreate##Type.notify(obj);\
		}

		OnCreateObject(WorldObject)
		OnCreateObject(PlayerModel)
		OnCreateObject(PlayerShotModel)

#undef OnCreateObject

	private:
		Observable<void(PlayerModel*, DoorModel*)> m_onIntoDoor;

	public:
		inline Observable<void(PlayerModel*, DoorModel*)>& onIntoDoor()
		{
			return m_onIntoDoor;
		}
	};
}