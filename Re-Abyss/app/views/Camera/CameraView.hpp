#pragma once

#include <Siv3D/Fwd.hpp>
#include <abyss/commons/Fwd.hpp>

namespace abyss
{
	class CameraView
	{
	private:
		const CameraModel*const m_pCamera;
		const ICameraWork* const m_pCameraWork;
	public:
		CameraView(const CameraModel* const pCamera, const ICameraWork* const pCameraWork);

		const s3d::Vec2& getCameraPos() const;
		void drawDeathLine() const;
		s3d::RectF screenRegion() const;
		s3d::Transformer2D getTransformer() const;

		void drawCameraWork() const;
	};
}
