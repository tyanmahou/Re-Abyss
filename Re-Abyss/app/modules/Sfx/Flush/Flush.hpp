#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/Sfx/Common/ColorFade.hpp>

namespace abyss::Sfx
{
	class Flush
	{
	public:
		void start(double time = 1.0, const s3d::ColorF& color = s3d::Palette::White);
		void start(double fadeInTime, double fadeOutTime, const s3d::ColorF& color = s3d::Palette::White);
		bool isFadeInEnd() const;
		bool isFadeOutEnd() const;
	public:
		void startFront(double time = 1.0, const s3d::ColorF& color = s3d::Palette::Black);
		void startFront(double fadeInTime, double fadeOutTime, const s3d::ColorF& color = s3d::Palette::Black);
	public:
		void update(double dt);
		void draw() const;
		void setManager(Manager* pManager)
		{
			m_pManager = pManager;
		}
	private:
		Manager* m_pManager;
		ColorFade m_base;
		ColorFade m_front;
	};
}