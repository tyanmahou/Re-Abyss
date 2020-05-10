#include "BaseState.hpp"
#include <abyss/commons/ActInclude.hpp>
#include <abyss/controllers/ActionSystem/ActionSystem.hpp>
namespace abyss::RollingTako
{
    void BaseState::setup()
    {
        m_body = this->m_pActor->find<BodyModel>().get();
    }
    void BaseState::update(double dt)
    {
        m_body->update(dt);
    }

    void BaseState::lastUpdate([[maybe_unused]] double dt)
    {
        if (auto colDir = m_body->fixPos(m_pActor->getModule<Camera>()->getCurrentRoom())) {
            this->onCollisionMap(colDir);
        }
    }

    void BaseState::draw() const
    {

    }
    void BaseState::onCollisionMap(ColDirection colDir)
    {
        if (colDir.isRight()) {
            m_body->setVelocityX(0);
            m_body->setForward(Forward::Right);
        }
        if (colDir.isLeft()) {
            m_body->setVelocityX(0);
            m_body->setForward(Forward::Left);
        }
    }
    void BaseState::onCollisionStay(IActor* col)
    {
        col->accept([this](const MapActor& map) {

            auto colDir = m_body->fixPos(map.getMapColInfo());

            if (colDir.isRight()) {
                m_body->setVelocityX(0);
                m_body->setForward(Forward::Right);
            }
            if (colDir.isLeft()) {
                m_body->setVelocityX(0);
                m_body->setForward(Forward::Left);
            }
        });
    }
}
