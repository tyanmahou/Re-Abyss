#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/modules/Actor/base/IPreDraw.hpp>
#include <abyss/components/Actor/Common/ColorAnim/IColorMul.hpp>
#include <abyss/components/Actor/Common/ColorAnim/IColorAdd.hpp>
#include <abyss/utils/TimeLite/Timer.hpp>

namespace abyss::Actor::Enemy::CodeZero
{
	/// <summary>
	/// 眼の制御
	/// </summary>
	class EyeCtrl :
		public IComponent,
		public IPreDraw,
		public ColorAnim::IColorMul,
		public ColorAnim::IColorAdd
	{
	public:
		EyeCtrl(ActorObj* pActor);

		void setVisible(bool isVisible, double fadeSec = 0.0);
		bool isAnimEnd() const;
		void flush(double timeSec = 1.0);

		double scale() const;

        bool isVisible() const;
	public:
		void onPreDraw() override;

		size_t indexMaskMul() const override
		{
			return 0x04;
		}
		s3d::ColorF colorMul() const override;

		size_t indexMaskAdd() const override
		{
			return 0x02;
		}
		s3d::ColorF colorAdd() const override;
	private:
		ActorObj* m_pActor = nullptr;
		bool m_isVisible = true;
		TimeLite::Timer m_timer;
		TimeLite::Timer m_flushTimer;
	};
}
namespace abyss
{
	template<>
	struct ComponentTree<Actor::Enemy::CodeZero::EyeCtrl>
	{
		using Base = MultiComponents<
			Actor::IPreDraw,
			Actor::ColorAnim::IColorMul,
			Actor::ColorAnim::IColorAdd
		>;
	};
}
