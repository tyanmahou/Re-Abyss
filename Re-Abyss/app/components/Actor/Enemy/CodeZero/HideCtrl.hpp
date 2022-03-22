#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/components/Actor/base/IDraw.hpp>

namespace abyss::Actor::Enemy::CodeZero
{
	class HideCtrl :
		public IComponent,
		public IDraw
	{
	public:
		HideCtrl(ActorObj* pActor);
		void setup(Executer executer) override;

		void onStart() override;
		void onEnd() override;
		void onDraw() const override;
	private:
		ActorObj* m_pActor = nullptr;
	};
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::Enemy::CodeZero::HideCtrl>
    {
        using Base = MultiComponents<
            Actor::IDraw
        >;
    };
}