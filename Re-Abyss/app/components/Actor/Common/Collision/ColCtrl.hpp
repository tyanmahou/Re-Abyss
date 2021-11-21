#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Actor/base/IPreCollision.hpp>
#include <abyss/components/Actor/Common/Collision/Node.hpp>

namespace abyss::Actor::Collision
{
	class ColCtrl : 
		public IComponent,
		public IPreCollision
	{
	public:
		ColCtrl(ActorObj* pActor);

		void setup(Executer executer);

		void onStart();
		void onEnd();

		void onPreCollision() override;
	private:
		ActorObj* m_pActor;
		s3d::uint64 m_id;
		s3d::Array<std::shared_ptr<Node>> m_nodes;
	};
}

namespace abyss
{
	template<>
	struct ComponentTree<Actor::Collision::ColCtrl>
	{
		using Base = MultiComponents<
			Actor::IPreCollision
		>;
	};
}
