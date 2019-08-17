#pragma once
#include "../WorldObject.hpp"

#include <Siv3D/Fwd.hpp>

namespace abyss
{
	class LadderModel : public WorldObject
	{
	private:
		bool m_isTop;
		s3d::Vec2 m_pos;
		s3d::Vec2 m_size;

	public:
		LadderModel(bool isTop, const s3d::Vec2& pos, const s3d::Vec2& size);
		s3d::Shape getCollider() const override;

		s3d::RectF region() const;
		s3d::Line getCenterLine() const;
		bool isTop() const;
		const s3d::Vec2& getPos() const;

		void draw()const override;
	};
}