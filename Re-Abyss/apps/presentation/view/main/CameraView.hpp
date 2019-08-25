#pragma once
#include <domain/model/CameraModel.hpp>
namespace abyss
{
	struct Transformer2D;

	class CameraView
	{
	private:
		const CameraModel*const m_pCamera;
	public:
		CameraView(const CameraModel* const pCamera);

		const s3d::Vec2& getCameraPos() const;
		void drawDeathLine() const;
		s3d::RectF screenRegion() const;
		abyss::Transformer2D getTransformer() const;
	};
}
