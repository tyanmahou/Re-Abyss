#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/components/Actor/Enemy/BabyDux/BuildDesc.hpp>

namespace abyss::Actor::Enemy::BabyDux
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

		double getAppearTime() const;
		const s3d::Vec2& getAppearMove() const;
	private:
		ActorObj* m_pActor = nullptr;
		BuildDesc m_desc;
		s3d::Vec2 m_parentPos;
	};
}
