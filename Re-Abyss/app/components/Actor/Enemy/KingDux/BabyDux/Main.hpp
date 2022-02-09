#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/components/Actor/Enemy/KingDux/BabyDux/BuildDesc.hpp>

namespace abyss::Actor::Enemy::KingDux::BabyDux
{
	class Main final :
		public IComponent
	{
	public:
		Main(ActorObj* pActor, const BuildDesc& desc, const s3d::Vec2& parentPos);

		const s3d::Vec2& parentPos() const
		{
			return m_parentPos;
		}
	private:
		ActorObj* m_pActor = nullptr;
		BuildDesc m_desc;
		s3d::Vec2 m_parentPos;
	};
}