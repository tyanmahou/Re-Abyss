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
		using CreateNotify = std::function<void(const std::shared_ptr<T>&, s3d::int32)>;

#define OnCreateObject(Type)\
    private:\
		CreateNotify<Type> m_onCreate##Type;\
    public:\
		inline void subscribe(CreateNotify<Type> callback)\
		{\
			m_onCreate##Type = callback;\
		}\
		inline void onCreateWorldObject(const std::shared_ptr<Type>& obj, s3d::int32 layer)\
		{\
			if (m_onCreate##Type) {\
				m_onCreate##Type(obj, layer);\
			}\
		}

		OnCreateObject(WorldObject)
		OnCreateObject(PlayerModel)
		OnCreateObject(PlayerShotModel)

#undef OnCreateObject
	};
}