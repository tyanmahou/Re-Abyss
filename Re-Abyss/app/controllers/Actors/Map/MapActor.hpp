#pragma once
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/types/MapColInfo.hpp>

namespace abyss
{
	class MapActor :public IActor
	{
	protected:
		ColDirection m_col;
		s3d::Vec2 m_pos;
		s3d::Vec2 m_size;

	public:
		MapActor(ColDirection col, const s3d::Vec2& pos, const s3d::Vec2& size);

		const s3d::Vec2& getPos() const;
		ColDirection getCol() const;
		s3d::RectF region() const;
		CShape getCollider() const override;

		void accept(const ActVisitor& visitor) override;

		MapColInfo getMapColInfo() const;
	};
}