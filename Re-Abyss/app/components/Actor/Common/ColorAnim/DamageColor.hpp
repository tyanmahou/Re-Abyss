#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/components/Actor/Common/DamageCtrl.hpp>
#include <abyss/components/Actor/Common/ColorAnim/IColorMul.hpp>

namespace abyss::Actor::ColorAnim
{
	/// <summary>
	/// ダメージカラー
	/// </summary>
	class DamageColor : 
		public IComponent,
		public IColorMul
	{
	public:
		DamageColor(ActorObj* pActor);

		s3d::ColorF colorMul() const override;

		void onStart() override;
	private:
		ActorObj* m_pActor;
		Ref<DamageCtrl> m_damageCtrl;
	};
}

namespace abyss
{
	template<>
	struct ComponentTree<Actor::ColorAnim::DamageColor>
	{
		using Base = MultiComponents<
			Actor::ColorAnim::IColorMul
		>;
	};
}