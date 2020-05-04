#include "DemoActor.hpp"

#include <abyss/views/actors/CodeZero/Body/BodyVM.hpp>
#include <abyss/views/actors/CodeZero/Hand/HandVM.hpp>
#include <abyss/views/actors/CodeZero/Head/HeadVM.hpp>
#include <abyss/types/Forward.hpp>

namespace abyss::CodeZero::Demo
{
    DemoActor::DemoActor(const s3d::Vec2& pos):
        m_pos(pos),
        m_bodyVM(std::make_unique<Body::BodyVM>()),
        m_headVM(std::make_unique<Head::HeadVM>()),
        m_leftHandVM(std::make_unique<Hand::HandVM>(Forward::Left)),
        m_rightHandVM(std::make_unique<Hand::HandVM>(Forward::Right))
    {}

    void DemoActor::draw() const
    {}

}
