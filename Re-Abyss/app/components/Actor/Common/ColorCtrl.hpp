#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/components/Actor/base/IPreDraw.hpp>
#include <abyss/components/Actor/Common/DamageCtrl.hpp>
#include <Siv3D/ColorF.hpp>

namespace abyss::Actor
{
	/// <summary>
	/// 色制御
	/// </summary>
	class ColorCtrl : 
		public IComponent,
		public IPreDraw
	{
	public:
		ColorCtrl(ActorObj* pActor);

		const s3d::ColorF& colorMul() const;
		const s3d::ColorF& colorAdd() const;
	public:
		void setup(Executer executer);
		void onStart()override;
		void onPreDraw()override;
	private:
		ActorObj* m_pActor = nullptr;

		s3d::ColorF m_colorMul{};
		s3d::ColorF m_colorAdd{};

		Ref<DamageCtrl> m_damageCtrl;

		TimeLite::Timer m_colorAnimTimer;
	};
}

namespace abyss
{
	template<>
	struct ComponentTree<Actor::ColorCtrl>
	{
		using Base = MultiComponents<
			Actor::IPreDraw
		>;
	};
}