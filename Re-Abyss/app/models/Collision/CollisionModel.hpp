#pragma once
#include<memory>
#include <unordered_set>

#include<Siv3D/Array.hpp>
#include <abyss/commons/Fwd.hpp>
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
		virtual void collisionAll(const s3d::Array<Ref<Actor::ICollision>>&) = 0;
		virtual void reset() = 0;
	};

	/// <summary>
	/// シンプルなあたり判定
	/// </summary>
	class SimpleCollision : public ICollisionModel
	{
	public:
		~SimpleCollision() override = default;
		void collisionAll(const s3d::Array<Ref<Actor::ICollision>>&) override;
		void reset()override;
	};
}