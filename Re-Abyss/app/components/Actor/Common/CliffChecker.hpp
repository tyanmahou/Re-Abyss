#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/components/Actor/base/IPrePhysics.hpp>

namespace abyss::Actor
{
	class CliffChecker:
		public IComponent,
		public IPrePhysics
	{
	private:
		class Impl;
	public:
		CliffChecker(ActorObj* pActor);

		CliffChecker& setFrontOffset(const s3d::Vec2& offset);
		CliffChecker& setBackOffset(const s3d::Vec2& offset);

		void onStart() override;
		void onEnd() override;

		void onPrePhysics() override;

		/// <summary>
		/// 崖
		/// </summary>
		/// <returns></returns>
		bool isCliff() const;

		/// <summary>
		/// 周りが崖か
		/// </summary>
		/// <returns></returns>
		bool isCliffAround() const;

		/// <summary>
		/// 前方のみ崖か
		/// </summary>
		/// <returns></returns>
		bool isCliffForwardOnly() const;
	private:
		std::unique_ptr<Impl> m_pImpl;
	};
}