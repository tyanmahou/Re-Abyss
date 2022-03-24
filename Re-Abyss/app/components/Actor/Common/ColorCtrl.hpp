#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/components/Actor/base/IPreDraw.hpp>
#include <abyss/components/Actor/Common/ColorAnim/IColorMul.hpp>
#include <abyss/components/Actor/Common/ColorAnim/IColorAdd.hpp>
#include <abyss/utils/Ref/Ref.hpp>
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

		s3d::Array<Ref<ColorAnim::IColorMul>> m_colorMulAnims;
		s3d::Array<Ref<ColorAnim::IColorAdd>> m_colorAddAnims;
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