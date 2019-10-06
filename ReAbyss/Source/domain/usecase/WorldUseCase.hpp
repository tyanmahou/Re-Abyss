#pragma once

#include "WorldObservable.hpp"
#include <domain/actor/IActor.hpp>
#include <application/util/CollisionPairHash.hpp>

#include <Siv3D/Array.hpp>
#include <Siv3D/Effect.hpp>

#include <memory>
#include <unordered_set>
namespace abyss
{
	class PlayerActor;
	class CameraModel;

	class WorldUseCase: public WorldObservable
	{
		const CameraModel* m_pCamera;
		std::shared_ptr<PlayerActor> m_playerModel = nullptr;

		s3d::Array<std::shared_ptr<IActor>> m_reserves;
		s3d::Array<std::shared_ptr<IActor>> m_objects;

		s3d::uint64 m_objIdCounter = 0;
		std::unordered_set<CollisionPairHash> m_currentCollision;

		void pushObject(const std::shared_ptr<IActor>& obj);

	public:
		template<class T, class... Args>
		void createObject(Args&& ... args)
		{
			auto obj = std::make_shared<T>(std::forward<Args>(args)...);
			this->registerObject(obj);
		}

		template<class Type>
		auto registerObject(const std::shared_ptr<Type>& object)
			->std::enable_if_t<std::is_base_of<IActor, Type>::value>
		{
			this->notifyCreateObject(object);
			this->pushObject(object);
		}

		void registerObject(const std::shared_ptr<PlayerActor>& obj);

		void update();
		void reset();

		PlayerActor* getPlayer()const;

		void setCamera(const CameraModel* camera);
		const CameraModel* getCamera()const;

	};
}


