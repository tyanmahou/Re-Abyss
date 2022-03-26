#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/components/Actor/base/IPreDraw.hpp>
#include <abyss/components/Actor/Common/DamageCtrl.hpp>
#include <abyss/components/Actor/Common/ColorAnim/IColorAdd.hpp>

namespace abyss::Actor::ColorAnim
{
	/// <summary>
	/// ダメージカラー
	/// </summary>
	class InvincibleColor :
		public IComponent,
		public IPreDraw,
		public IColorAdd
	{
	public:
		InvincibleColor(ActorObj* pActor);

		void startAnim(double sec);
		void endAnim();

		void onStart() override;

		void onPreDraw() override;

		s3d::ColorF colorAdd() const override;
	private:
		ActorObj* m_pActor;
		Ref<DamageCtrl> m_damageCtrl;
		TimeLite::Timer m_colorAnimTimer;
	};
}

namespace abyss
{
	template<>
	struct ComponentTree<Actor::ColorAnim::InvincibleColor>
	{
		using Base = MultiComponents<
			Actor::IPreDraw,
			Actor::ColorAnim::IColorAdd
		>;
	};
}