#include "PosModel.hpp"

namespace abyss
{
    PosModel::PosModel(s3d::Vec2& pos)
    {
        this->initPos(pos);
    }
    PosModel& PosModel::initPos(const s3d::Vec2& pos)
    {
        m_pos = pos;
        m_prevPos = pos;
        return *this;
    }
    PosModel& PosModel::setPos(const s3d::Vec2& pos)
    {
        m_pos = pos;
        return *this;
    }
    PosModel& PosModel::setPosX(double x)
    {
        m_pos.x = x;
        return *this;
    }
    PosModel& PosModel::setPosY(double y)
    {
        m_pos.y = y;
        return *this;
    }
    PosModel& PosModel::addPos(const s3d::Vec2& deltaPos)
    {
        m_pos += deltaPos;
        return *this;
    }
    PosModel& PosModel::addPosX(double deltaX)
    {
        m_pos.x += deltaX;
        return *this;
    }
    PosModel& PosModel::addPosY(double deltaY)
    {
        m_pos.y += deltaY;
        return *this;
    }
    const s3d::Vec2& PosModel::getPos() const
    {
        return m_pos;
    }
    const s3d::Vec2& PosModel::getPrevPos() const
    {
        return m_prevPos;
    }
}
