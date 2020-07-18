#include "LadderState.hpp"
#include <abyss/views/Actors/Player/PlayerVM.hpp>
#include <abyss/commons/InputManager/InputManager.hpp>
#include <abyss/controllers/Actors/Map/Ladder/LadderActor.hpp>
#include <abyss/params/Actors/Player/Param.hpp>

namespace abyss::Player
{
    void LadderState::onMove(double dt)
    {
        if (InputManager::A.down()) {
            this->changeState(State::Swim);
            return;
        }
        if (m_attackCtrl->isAttacking()) {
            return;
        }
        double veocityY = Param::Ladder::Speed * (InputManager::Down.pressed() - InputManager::Up.pressed());
        m_body->setVelocity({ 0, veocityY });
        m_body->update(dt);

    }
    void LadderState::onLanding()
    {
        this->changeState(PlayerActor::State::Swim);
    }
    void LadderState::onCollisionStayLadderTop(const LadderActor& ladder)
    {
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
    void LadderState::start()
    {
        m_body->noneResistanced();
    }
    void LadderState::update(double dt)
    {
        BaseState::update(dt);
        if (m_isTop && InputManager::Up.pressed()) {
            m_ladderTopTimer += 60 * dt;
        }
    }
    void LadderState::lastUpdate()
    {
        BaseState::lastUpdate();
        if (!m_foot->isLadder()) {
            this->changeState(PlayerActor::State::Swim);
        }
    }
    void LadderState::onDraw(const PlayerVM& view) const
    {
        if (this->isLadderTop()) {
            view.drawStateLadderTop();
        } else {
            view.drawStateLadder();
        }
    }
    bool LadderState::isLadderTop() const
    {
        return m_isTop;
    }
}