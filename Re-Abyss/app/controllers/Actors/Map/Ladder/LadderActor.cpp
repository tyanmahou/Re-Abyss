#include "LadderActor.hpp"
#include <Siv3D.hpp>
#include <abyss/components/Actors/Map/Ladder/LadderProxy.hpp>

namespace abyss::Actor::Map::Ladder
{
	LadderActor::LadderActor(ColDirection col, const s3d::Vec2& pos, const s3d::Vec2& size):
		MapActor(col, pos, size)
	{
		m_tag = Tag::Ladder{};

		this->attach<LadderProxy>(this);
	}

	s3d::Line LadderActor::getCenterLine() const
	{
		const auto& pos = this->getPos();
		const auto& size = this->getSize();

		Vec2 beginY = pos - Vec2{ 0, size.y/2.0 + 1.0 };
		Vec2 endY = pos + Vec2{ 0, size.y / 2.0 - 10.0};
		return s3d::Line(beginY, endY);
	}
	bool LadderActor::isTop() const
	{
		return (m_col & ColDirection::Up) != ColDirection::None;
	}
}