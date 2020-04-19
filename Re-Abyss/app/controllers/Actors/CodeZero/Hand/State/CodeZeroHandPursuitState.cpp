#include "CodeZeroHandPursuitState.hpp"
#include <abyss/controllers/Actors/Player/PlayerActor.hpp>
#include <abyss/controllers/Actors/CodeZero/CodeZeroActor.hpp>
#include <abyss/params/Actors/CodeZero/CodeZeroParam.hpp>

namespace abyss
{
    void CodeZeroHandPursuitState::updateRight(double dt)
    {
        double rotate = m_rotate->addRotate(dt).getRotate();
        constexpr auto limit = Math::ToRadians(50);
        if (rotate >= limit) {
            m_rotate->setRotate(limit);
        }
        auto playerPos = m_actor->getModule<PlayerActor>()->getPos();
        const auto& pos = m_body->getPos();
        if (playerPos.x - 60 >= pos.x) {
            m_body->setVelocityX(CodeZeroParam::Hand::PursuitSpeed);
        } else if (playerPos.x + 60 <= pos.x) {
            m_body->setVelocityX(-CodeZeroParam::Hand::PursuitSpeed);
        }

        m_body->update(dt);

        double border = m_parent->getPos().y - 250;
        if (m_body->getPos().y <= border) {
            m_body->setPosY(border);
        }
    }
    void CodeZeroHandPursuitState::updateLeft(double dt)
    {
        double rotate = m_rotate->addRotate(dt).getRotate();
        constexpr auto limit = Math::ToRadians(40);
        if (rotate >= limit) {
            m_rotate->setRotate(limit);
        }
        auto playerPos = m_actor->getModule<PlayerActor>()->getPos();
        const auto& pos = m_body->getPos();
        if (playerPos.y - 60 >= pos.y) {
            m_body->setVelocityY(CodeZeroParam::Hand::PursuitSpeed);
        } else if (playerPos.y + 60 <= pos.y) {
            m_body->setVelocityY(-CodeZeroParam::Hand::PursuitSpeed);
        }

        m_body->update(dt);

        double border = m_parent->getPos().x + 400;
        if (m_body->getPos().x >= border) {
            m_body->setPosX(border);
        }
    }
    void CodeZeroHandPursuitState::start()
    {
        if (m_actor->isLeftHand()) {
            m_body->setVelocityY(CodeZeroParam::Hand::PursuitSpeed);
            m_body->setVelocityX(CodeZeroParam::Hand::SetUpSpeed);
        } else {
            m_body->setVelocityY(-CodeZeroParam::Hand::SetUpSpeed);
            m_body->setVelocityX(CodeZeroParam::Hand::PursuitSpeed);
        }
    }
}
