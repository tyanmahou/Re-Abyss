#pragma once
#include <functional>
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/GameObject/IComponent.hpp>
#include <Siv3D/Array.hpp>

namespace abyss::Adv
{
	/// <summary>
	/// スキップ制御
	/// </summary>
	class SkipCtrl : public IComponent
	{
	public:
		SkipCtrl(AdvObj* pObj);

		SkipCtrl& registCallback(const std::function<void()>& callback);

		bool isSkip() const;
		void onSkip();

        bool isEnabled() const
        {
            return m_isEnabled;
        }
		SkipCtrl& setIsEnabled(bool isEnabled)
		{
			m_isEnabled = isEnabled;
			return *this;
		}
	private:
        AdvObj* m_pObj;
		s3d::Array<std::function<void()>> m_callbacks;
		bool m_isEnabled = false;
	};
}
