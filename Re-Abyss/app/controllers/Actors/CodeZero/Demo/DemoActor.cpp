#include "DemoActor.hpp"

#include <abyss/views/actors/CodeZero/Body/BodyVM.hpp>
#include <abyss/views/actors/CodeZero/Hand/HandVM.hpp>
#include <abyss/views/actors/CodeZero/Head/HeadVM.hpp>
#include <abyss/params/Actors/CodeZero/Param.hpp>
#include <abyss/types/Forward.hpp>

namespace abyss::CodeZero::Demo
{
    DemoActor::DemoActor(const s3d::Vec2& pos):
        m_pos(pos),
        m_bodyVM(std::make_unique<Body::BodyVM>()),
        m_headVM(std::make_unique<Head::HeadVM>()),
        m_leftHandVM(std::make_unique<Hand::HandVM>(Forward::Left)),
        m_rightHandVM(std::make_unique<Hand::HandVM>(Forward::Right))
    {
        m_order = -99;
    }

    void DemoActor::draw() const
    {
        m_bodyVM->setPos(m_pos).draw();
        m_headVM->setPos(m_pos + Param::Head::Offset).draw();
        m_leftHandVM->setPos(m_pos + s3d::Vec2{ 110, 90 }).draw();
        m_rightHandVM->setPos(m_pos + s3d::Vec2{ -110, 90 }).draw();
    }

}
