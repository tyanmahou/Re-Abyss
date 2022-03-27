#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/components/Actor/base/IDraw.hpp>
#include <abyss/components/Actor/Common/ColorAnim/IColorMul.hpp>

namespace abyss::Actor::Enemy::CodeZero
{
	class HideCtrl :
		public IComponent,
		public IDraw,
		public ColorAnim::IColorMul
	{
	public:
		HideCtrl(ActorObj* pActor);
		void setup(Executer executer) override;

		void onStart() override;
		void onEnd() override;
		void onDraw() const override;

		s3d::ColorF colorMul() const override;
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
            Actor::IDraw,
			ColorAnim::IColorMul
        >;
    };
}