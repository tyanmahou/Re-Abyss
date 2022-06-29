#include <abyss/modules/Camera/CameraParam.hpp>
#include <abyss/commons/Constants.hpp>
using namespace s3d;

namespace abyss
{
	CameraParam::CameraParam():
		m_pos(Constants::GameScreen.center()),
		m_targetPos(Constants::GameScreen.center())
	{}
	void CameraParam::setPos(const s3d::Vec2 pos)
	{
		m_pos = pos;
	}
	const s3d::Vec2& CameraParam::getPos() const
	{
		return m_pos;
	}
	void CameraParam::setTargetPos(const s3d::Vec2 pos)
	{
		m_targetPos = pos;
	}
	const s3d::Vec2& CameraParam::getTargetPos() const
	{
		return m_targetPos;
	}
}
