#pragma once

#include <Siv3D/Vector2D.hpp>
#include <Siv3D/Stopwatch.hpp>
#include <Siv3D/Mat3x2.hpp>
#include <Siv3D/Transformer2D.hpp>
#include <abyss/modules/Room/RoomData.hpp>

#include <memory>

namespace abyss
{
	class CameraParam
	{
    public:
        static s3d::Transformer2D Transformer(const s3d::Mat3x2& mat);
	public:
		CameraParam();

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

        s3d::Vec2 tl() const;
        s3d::RectF screenRegion() const;
        s3d::RectF resolutionRegion() const;

        s3d::Vec2 adjustTargetPos() const;
        s3d::Mat3x2 getMat() const;
        s3d::Transformer2D getTransformer() const;
    private:
        s3d::Vec2 m_pos;
        s3d::Vec2 m_targetPos;
        double m_zoomScale = 1.0;
	};
}
