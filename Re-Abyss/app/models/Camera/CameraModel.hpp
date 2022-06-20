#pragma once

#include <Siv3D/Vector2D.hpp>
#include <Siv3D/Graphics.hpp>
#include <Siv3D/Stopwatch.hpp>
#include <abyss/modules/Room/RoomData.hpp>

#include <memory>

namespace abyss
{
	class CameraModel
	{
	private:
		s3d::Vec2 m_pos;
		s3d::Vec2 m_targetPos;
		double m_zoomScale = 1.0;

	public:
		CameraModel();

		void setPos(const s3d::Vec2 pos);
		const s3d::Vec2& getPos()const;

		void setTargetPos(const s3d::Vec2 pos);
		const s3d::Vec2& getTargetPos()const;

		void setZoomScale(double scale)
		{
			m_zoomScale = scale;
		}
		double getZoomScale()const
		{
			return m_zoomScale;
		}
	};
}
