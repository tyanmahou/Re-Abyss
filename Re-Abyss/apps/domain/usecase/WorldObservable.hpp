#pragma once
#include <functional>
#include <memory>
#include <Siv3D/Fwd.hpp>

namespace abyss
{
	class WorldObject;
	class PlayerModel;
	class PlayerShotModel;

	class WorldObservable
	{
		template<class T>
		using CreateNotify = std::function<void(const std::shared_ptr<T>&)>;

#define OnCreateObject(Type)\
    private:\
		CreateNotify<Type> m_onCreate##Type;\
    public:\
		inline void subscribe(CreateNotify<Type> callback)\
		{\
			m_onCreate##Type = callback;\
		}\
		inline void onCreateWorldObject(const std::shared_ptr<Type>& obj)\
		{\
			if (m_onCreate##Type) {\
				m_onCreate##Type(obj);\
			}\
		}

		OnCreateObject(WorldObject)
		OnCreateObject(PlayerModel)
		OnCreateObject(PlayerShotModel)

#undef OnCreateObject
	};
}