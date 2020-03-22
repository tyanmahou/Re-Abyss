#include "PlayerLadderState.hpp"
#include <abyss/views/Actors/Player/PlayerVM.hpp>
#include <abyss/commons/InputManager/InputManager.hpp>
#include <abyss/controllers/Actors/Ladder/LadderActor.hpp>

namespace abyss
{
    void PlayerLadderState::onMove(double dt)
    {
        double veocityY = 120.0 * (InputManager::Down.pressed() - InputManager::Up.pressed());
        m_body->setVelocity({ 0, veocityY });
        m_body->update(dt);
        if (InputManager::A.down()) {
            this->changeState(PlayerActor::State::Swim);
        }
    }
    void PlayerLadderState::onLanding()
    {
        m_isLanding = true;
        this->changeState(PlayerActor::State::Swim);
    }
    void PlayerLadderState::onCollisionStay(const LadderActor& ladder)
    {
        if (ladder.isTop()) {
            auto&& ladderRegion = ladder.region();

            //上端にきたら状態を繊維する
            if (m_body->getPos().y <= ladderRegion.y) {
                if (!m_isTop) {
                    m_ladderTopTimer = 0;
                    m_isTop = true;
                }
                m_body->setPosY(ladderRegion.y);
            } else {
                m_isTop = false;
            }
            if (m_isTop && (InputManager::Up.down() || m_ladderTopTimer > 5.0)) {
                m_body->setPosY(ladderRegion.y - m_body->region().h / 2.0);
                this->changeState(PlayerActor::State::Swim);
            }
        }
        if (ladder.getCenterLine().intersects(m_body->region())) {
            m_canLadder = true;
        }
    }
    void PlayerLadderState::start()
    {
        m_body->noneResistanced();
    }
    void PlayerLadderState::update(double dt)
    {
        if (!m_canLadder) {
            this->changeState(PlayerActor::State::Swim);
        }
        PlayerBaseState::update(dt);
        m_canLadder = false;
        if (m_isTop && InputManager::Up.pressed()) {
            m_ladderTopTimer += 60 * dt;
        }
    }
    void PlayerLadderState::onDraw(const PlayerVM& view) const
    {
        if (m_isLanding) {
            view.drawStateStay();
        }else if (!m_canLadder) {
            view.drawStateFloat();
        }else if (this->isLadderTop()) {
            view.drawStateLadderTop();
        } else {
            view.drawStateLadder();
        }
    }
    bool PlayerLadderState::isLadderTop() const
    {
        return m_isTop;
    }
}