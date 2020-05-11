#include "BaseState.hpp"
#include <abyss/commons/ActInclude.hpp>
#include <abyss/controllers/ActionSystem/ActionSystem.hpp>
#include <abyss/params/Actors/Enemy/Slime/Param.hpp>
namespace abyss::Slime
{
    void BaseState::setup()
    {
        m_body = this->m_pActor->find<BodyModel>().get();
    }
    void BaseState::update(double dt)
    {
        m_body->setAccelX(m_body->getForward() * Param::Walk::AccelX);
        m_body->update(dt);
    }
    void BaseState::draw() const
    {}

    void BaseState::onCollisionStay(IActor * col)
    {
        col->accept([this](const MapActor& map) {

            auto colDir = m_body->fixPos(map.getMapColInfo());
            if (colDir.isUp()) {
                onColisionMapUp();
            }
            if (colDir.isRight()) {
                m_body->setForward(Forward::Right);
            }
            if (colDir.isLeft()) {
                m_body->setForward(Forward::Left);
            }
        });
    }
    void BaseState::lastUpdate([[maybe_unused]]double dt)
    {
        if (auto colDir = m_body->fixPos(m_pActor->getModule<Camera>()->getCurrentRoom())) {
            if (colDir.isRight()) {
                m_body->setForward(Forward::Right);
            }
            if (colDir.isLeft()) {
                m_body->setForward(Forward::Left);
            }
        }
    }
}
