#pragma once
#include <abyss/commons/Fwd.hpp>
#include <Siv3D/Vector2D.hpp>
#include <Siv3D/Optional.hpp>
#include <abyss/entities/Actor/Item/RecoveryEntity.hpp>

namespace abyss::Actor::Item
{
	struct RecoveryEntity;
}
namespace abyss::Actor::Item::Recovery
{
	struct Builder
	{
		static void Build(ActorObj* pActor, const RecoveryEntity& entity);

		// 直接生成
		static void Build(ActorObj* pActor, const s3d::Vec2& pos, RecoveryKind kind);
		static void Build(ActorObj* pActor, const s3d::Vec2& pos, RecoveryKind kind, const s3d::Optional<s3d::uint32>& objId);
	};
}