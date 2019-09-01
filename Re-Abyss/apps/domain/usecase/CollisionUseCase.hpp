#pragma once
#include<Siv3D/Array.hpp>
#include<memory>

#include <unordered_set>
#include <application/util/CollisionPairHash.hpp>

namespace abyss
{
	class WorldObject;

	class ICollisionUseCase
	{
	public:
		virtual void collisionAll(s3d::Array<std::shared_ptr<WorldObject>>&) = 0;
		virtual void reset() = 0;
	};

	class SimpleCollision : public ICollisionUseCase
	{
		std::unordered_set<CollisionPairHash> m_currentCollision;
	public:
		void collisionAll(s3d::Array<std::shared_ptr<WorldObject>>& objects) override;
		void reset()override;
	};
}