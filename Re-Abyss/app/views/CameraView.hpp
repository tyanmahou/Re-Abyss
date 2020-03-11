#pragma once

#include <Siv3D/Fwd.hpp>
#include <abyss/commons/Fwd.hpp>

namespace abyss
{
	class CameraView
	{
	private:
		const CameraModel*const m_pCamera;
	public:
		CameraView(const CameraModel* const pCamera);

		const s3d::Vec2& getCameraPos() const;
		void drawDeathLine() const;
		s3d::RectF screenRegion() const;
		s3d::Transformer2D getTransformer() const;
	};
}
