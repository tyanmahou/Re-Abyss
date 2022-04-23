#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/Sfx/Common/ColorFade.hpp>

namespace abyss::Sfx
{
	class SkipFade
	{
	public:
		void start(double time = 1.0, const s3d::ColorF& color = s3d::Palette::Black);
		void start(double fadeInTime, double fadeOutTime, const s3d::ColorF& color = s3d::Palette::Black);
		bool isFadeInEnd() const;
		bool isFadeOutEnd() const;
	public:
		void update(double dt);
		void draw() const;
		void setManager(Manager* pManager)
		{
			m_pManager = pManager;
		}
	private:
		Manager* m_pManager;
		ColorFade m_fade;
	};
}