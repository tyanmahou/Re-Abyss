#include "JumpState.hpp"
#include "WalkState.hpp"

#include <abyss/params/Actors/Enemy/Slime/Param.hpp>
namespace abyss::Slime
{
    void JumpState::start()
    {
        m_pActor->find<AudioSourceModel>()->play(U"Jump");
        m_body->setSize(Param::Jump::Size).setPivot({ 0, 0 });

        m_body->jumpToHeight(Param::Jump::JumpHeight);
        
        m_draw->request(DrawModel::Kind::Jump);
    }
    void JumpState::lastUpdate()
    {
        if (m_mapCol->isHitGround()) {
            this->changeState<WalkState>();
        }
        BaseState::lastUpdate();
    }
}
