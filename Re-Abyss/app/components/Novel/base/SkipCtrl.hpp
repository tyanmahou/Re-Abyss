#pragma once
#include <functional>
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/GameObject/IComponent.hpp>
#include <Siv3D/Array.hpp>

namespace abyss::Novel
{
	/// <summary>
	/// スキップ制御
	/// </summary>
	class SkipCtrl : public IComponent
	{
	public:
		SkipCtrl(TalkObj* pTalk);

		SkipCtrl& registCallback(const std::function<void()>& callback);

		bool isSkip() const;
		void onSkip();
	private:
		TalkObj* m_pTalk;
		s3d::Array<std::function<void()>> m_callbacks;
	};
}