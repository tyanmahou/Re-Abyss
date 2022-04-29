#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/components/Actor/Common/DrawBase.hpp>
#include <abyss/components/Actor/base/IPreDraw.hpp>
#include <abyss/components/Actor/Common/ColorAnim/IColorMul.hpp>
#include <abyss/utils/TimeLite/Timer.hpp>

namespace abyss::Actor::Enemy::CodeZero
{
	class HideCtrl :
		public IComponent,
		public IPreDraw,
		public DrawBase,
		public ColorAnim::IColorMul
	{
	public:
		HideCtrl(ActorObj* pActor);

		void setVisible(bool isVisible, double fadeSec = 0.0);
		bool isAnimEnd() const;

		double calcBackAlpha() const;
	public:
		void setup(Executer executer) override;

		void onStart() override;
		void onEnd() override;

		void onPreDraw() override;
		void onDraw() const override;

		size_t indexMaskMul() const override
		{
			return 0x01 | 0x02;
		}
		s3d::ColorF colorMul() const override;
	private:
		ActorObj* m_pActor = nullptr;
		bool m_isVisible = true;
		TimeLite::Timer m_timer;
	};
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::Enemy::CodeZero::HideCtrl>
    {
        using Base = MultiComponents<
			Actor::IPreDraw,
            Actor::DrawBase,
			Actor::ColorAnim::IColorMul
        >;
    };
}