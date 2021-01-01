#include "MoveSwim.hpp"
#include <abyss/commons/InputManager/InputManager.hpp>

#include <abyss/modules/Actors/base/IActor.hpp>
#include <abyss/components/Actors/Commons/AudioSource.hpp>
#include <abyss/components/Actors/Commons/Body.hpp>
#include <abyss/components/Actors/Commons/BodyUpdater.hpp>
#include <abyss/components/Actors/Commons/Foot.hpp>
#include <abyss/components/Actors/Player/ForwardCtrl.hpp>

#include <abyss/params/Actors/Player/Param.hpp>

namespace abyss::Actor::Player
{
    MoveSwim::MoveSwim(IActor* pActor):
        m_pActor(pActor)
    {}

    void MoveSwim::setup(Executer executer)
    {
        executer.on<IMove>().addAfter<ForwardCtrl>();
        executer.on<IMove>().addBefore<BodyUpdater>();
    }

    void MoveSwim::onStart()
    {
        m_body = m_pActor->find<Body>();
        m_foot = m_pActor->find<Foot>();
    }

    void MoveSwim::onMove()
    {
        if (!m_isActive) {
            return;
        }
        const bool rightPressed = InputManager::Right.pressed();
        const bool leftPressed = InputManager::Left.pressed();

        m_body->setAccelX(Param::Swim::AccelX * (rightPressed - leftPressed));
        // ジャンプ
        if (InputManager::Jump.down()) {
            m_body->jumpToHeight(Param::Swim::JumpHeight);
            m_pActor->find<AudioSource>()->play(U"Swim");
        }
        if (InputManager::Down.pressed()) {
            m_body->setMaxVelocityY(Param::Swim::DiveSpeed);
        } else {
            m_body->setMaxVelocityY(Body::DefaultMaxVelocityY);
        }

        // 降りる
        if (m_foot->isDownable() && InputManager::Down.down()) {
            m_body->addPosY(10.0);
        }
    }

    void MoveSwim::onStateStart()
    {
        m_isActive = false;
    }
}
