#include "LadderModel.hpp"
#include <Siv3D.hpp>

namespace abyss
{
	LadderModel::LadderModel(bool isTop, const s3d::Vec2& pos, const s3d::Vec2& size):
		m_isTop(isTop),
		m_pos(pos),
		m_size(size)
	{
		this->tag = L"ladder";
	}
	s3d::Shape LadderModel::getCollider() const
	{
		return static_cast<Shape>(this->region());
	}
	s3d::RectF LadderModel::region() const
	{
		return RectF{ m_pos - m_size / 2, m_size };
	}
	s3d::Line LadderModel::getCenterLine() const
	{
		Vec2 beginY = m_pos - Vec2{ 0, m_size.y/2.0 + 1.0 };
		Vec2 endY = m_pos + Vec2{ 0, m_size.y / 2.0 - 10.0};
		return s3d::Line(beginY, endY);
	}
	bool LadderModel::isTop() const
	{
		return m_isTop;
	}
	const s3d::Vec2& LadderModel::getPos() const
	{
		return m_pos;
	}
	void LadderModel::draw() const
	{
#ifdef DEBUG
		Color c = m_isTop ? Palette::Red : Palette::Blue;
		this->region().draw(c.setAlpha(128));
		this->getCenterLine().draw(5, c.setAlpha(128));
#endif // DEBUG
	}
}