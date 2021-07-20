#include "LadderState.hpp"
#include "SwimState.hpp"
#include <abyss/views/Actor/Player/PlayerVM.hpp>
#include <abyss/commons/InputManager/InputManager.hpp>
#include <abyss/components/Actor/Player/ForwardCtrl.hpp>
#include <abyss/params/Actor/Player/Param.hpp>

namespace abyss::Actor::Player
{
    void LadderState::onLanding()
    {
        this->changeState<SwimState>();
    }

    void LadderState::start()
    {
        m_body->noneResistanced();
        // 攻撃可能
        m_attackCtrl->setActive(true);

        m_pActor->find<ForwardCtrl>()->setActive(true);
    }
    void LadderState::update()
    {
        auto dt = m_pActor->deltaTime();

        if (m_foot->isLadderTop()) {
            //上端にきたら状態を繊維する
            auto topY = m_foot->getLadderInfo()->pos.y;
            if (m_body->getPos().y <= topY) {
                if (!m_isTop) {
                    m_ladderTopTimer = 0;
                    m_isTop = true;
                }
                m_body->setPosY(topY);
            } else {
                m_isTop = false;
            }
            if (m_isTop && (InputManager::Up.down() || m_ladderTopTimer > 5.0)) {
                m_body->setPosY(topY - m_body->region().h / 2.0);
                this->changeState<SwimState>();
                return;
            }
        }

        {
            if (InputManager::A.down()) {
                this->changeState<SwimState>();
                return;
            }
            double veocityY = Param::Ladder::Speed * (InputManager::Down.pressed() - InputManager::Up.pressed());
            m_body->setVelocity({ 0, veocityY });
        }

        if (m_isTop && InputManager::Up.pressed()) {
            m_ladderTopTimer += 60 * dt;
        }
    }
    void LadderState::lastUpdate()
    {
        BaseState::lastUpdate();
        if (!m_foot->isLadder()) {
            this->changeState<SwimState>();
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