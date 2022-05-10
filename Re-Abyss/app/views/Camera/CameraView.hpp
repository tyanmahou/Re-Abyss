#pragma once
#include <Siv3D/Fwd.hpp>
#include <Siv3D/Vector2D.hpp>
#include <Siv3D/Mat3x2.hpp>
#include <Siv3D/Transformer2D.hpp>
#include <abyss/commons/Fwd.hpp>

namespace abyss
{
	class CameraView
	{
	public:
		static s3d::Transformer2D Transformer(const s3d::Mat3x2& mat);
	public:
		CameraView(const CameraModel* const pCamera, const s3d::Vec2& quakeOffset);

		const s3d::Vec2& getCameraPos() const;
		const s3d::Vec2& getQuakeOffset() const;
		void drawDeathLine() const;

		s3d::Vec2 tl() const;
		s3d::RectF screenRegion() const;
		s3d::RectF resolutionRegion() const;

		s3d::Vec2 adjustTargetPos() const;
		s3d::Mat3x2 getMat() const;
		s3d::Transformer2D getTransformer() const;

	private:
		const CameraModel* const m_pCamera;
		const s3d::Vec2 m_quakeOffset;
	};
}
