#pragma once
#include<memory>
#include <unordered_set>

#include<Siv3D/Array.hpp>
#include <abyss/commons/Fwd.hpp>
#include <abyss/types/CollisionPairHash.hpp>
#include <abyss/utils/Ref/Ref.hpp>
namespace abyss
{
	/// <summary>
	/// 当たり判定インターフェース
	/// </summary>
	class ICollisionModel
	{
	public:
		ICollisionModel() = default;
		virtual ~ICollisionModel() = default;
		virtual void collisionAll(const s3d::Array<Ref<IColliderModel>>&) = 0;
		virtual void collisionAll(const s3d::Array<std::shared_ptr<IActor>>&) = 0;
		virtual void reset() = 0;
	};

	/// <summary>
	/// シンプルなあたり判定
	/// </summary>
	class SimpleCollision : public ICollisionModel
	{
		std::unordered_set<CollisionPairHash> m_currentCollision;
	public:
		~SimpleCollision() override = default;
		void collisionAll(const s3d::Array<Ref<IColliderModel>>&) override;
		void collisionAll(const s3d::Array<std::shared_ptr<IActor>>& objects) override;
		void reset()override;
	};
}