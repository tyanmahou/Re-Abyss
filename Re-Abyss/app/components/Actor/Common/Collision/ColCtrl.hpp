#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/modules/Collision/Branch.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Actor::Collision
{
	class ColCtrl : 
		public IComponent
	{
	public:
		ColCtrl(ActorObj* pActor);

		void setup(Executer executer);

		void onStart();
		void onEnd();
	private:
		ActorObj* m_pActor;
		s3d::uint64 m_id;
		s3d::Array<Ref<abyss::Collision::Branch>> m_branch;
	};
}