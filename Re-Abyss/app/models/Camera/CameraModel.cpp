#include "CameraModel.hpp"
#include <abyss/commons/Constants.hpp>
using namespace s3d;

namespace abyss
{

	CameraModel::CameraModel():
		m_pos(Constants::GameScreen.center()),
		m_targetPos(Constants::GameScreen.center())
	{}
	void CameraModel::setPos(const s3d::Vec2 pos)
	{
		m_pos = pos;
	}
	const s3d::Vec2& CameraModel::getPos() const
	{
		return m_pos;
	}
	void CameraModel::setTargetPos(const s3d::Vec2 pos)
	{
		m_targetPos = pos;
	}
	const s3d::Vec2& CameraModel::getTargetPos() const
	{
		return m_targetPos;
	}
}