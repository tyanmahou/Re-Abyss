#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/components/Actor/base/IPreDraw.hpp>
#include <abyss/components/Actor/Common/ColorAnim/ColorMulBase.hpp>
#include <abyss/utils/TimeLite/Timer.hpp>

namespace abyss::Actor::ColorAnim
{
	/// <summary>
	/// ボス撃破カラー
	/// </summary>
	class BossDeadColor :
		public IComponent,
		public IPreDraw,
		public ColorMulBase
	{
	public:
		BossDeadColor(ActorObj* pActor);

		void startAnim(double blackFadeSec = 6.0, double alphaFadeSec = 2.0);
	public:
		void onPreDraw() override;

		s3d::ColorF colorMul() const override;
	private:
		ActorObj* m_pActor;
		TimeLite::Timer m_blackFadeTimer;
		TimeLite::Timer m_alphaFadeTimer;

		bool m_isStarted = false;
	};
}

namespace abyss
{
	template<>
	struct ComponentTree<Actor::ColorAnim::BossDeadColor>
	{
		using Base = MultiComponents<
			Actor::IPreDraw,
			Actor::ColorAnim::ColorMulBase
		>;
	};
}