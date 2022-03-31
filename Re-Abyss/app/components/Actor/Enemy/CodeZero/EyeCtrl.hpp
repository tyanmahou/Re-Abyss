#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/components/Actor/base/IPreDraw.hpp>
#include <abyss/components/Actor/Common/ColorAnim/IColorMul.hpp>
#include <abyss/utils/TimeLite/Timer.hpp>

namespace abyss::Actor::Enemy::CodeZero
{
	/// <summary>
	/// 眼の制御
	/// </summary>
	class EyeCtrl :
		public IComponent,
		public IPreDraw,
		public ColorAnim::IColorMul
	{
	public:
		EyeCtrl(ActorObj* pActor);

		void setVisible(bool isVisible, double fadeSec = 0.0);
		bool isAnimEnd() const;
	public:
		void onPreDraw() override;

		size_t indexMask() const override
		{
			return 0x04;
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
	struct ComponentTree<Actor::Enemy::CodeZero::EyeCtrl>
	{
		using Base = MultiComponents<
			Actor::IPreDraw,
			Actor::ColorAnim::IColorMul
		>;
	};
}