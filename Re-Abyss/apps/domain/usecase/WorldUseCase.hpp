#pragma once

#include "../model/object/WorldObject.hpp"
#include "../../application/util/CollisionPairHash.hpp"

#include <Siv3D/Array.hpp>
#include <Siv3D/Effect.hpp>

#include <memory>
#include <unordered_set>
namespace abyss
{
	class PlayerModel;

	class WorldUseCase
	{
		PlayerModel* m_playerModel = nullptr;

		s3d::Array<std::shared_ptr<WorldObject>> m_reserves;
		s3d::Array<std::shared_ptr<WorldObject>> m_objects;

		s3d::uint64 m_objIdCounter = 0;
		std::unordered_set<CollisionPairHash> m_currentCollision;

		s3d::Effect m_effect;
	public:
		template<class T, class... Args>
		void createObject(Args&& ... args)
		{
			auto obj = std::make_shared<T>(std::forward<Args>(args)...);
			this->registerObject(obj);
		}

		void registerObject(const std::shared_ptr<WorldObject>& obj);

		void registerObject(const std::shared_ptr<PlayerModel>& obj);

		void update();

		void draw()const;

		s3d::Effect& getEffect();
	};

}


