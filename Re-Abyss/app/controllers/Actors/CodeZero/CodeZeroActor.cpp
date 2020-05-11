#include <abyss/models/Actors/CodeZero/State/Phase1State.hpp>
#include <abyss/models/Actors/CodeZero/State/Phase2State.hpp>
#include <abyss/models/Actors/CodeZero/State/Phase3State.hpp>
#include <abyss/entities/Actors/Enemy/CodeZeroEntity.hpp>
#include <abyss/views/Actors/CodeZero/Body/BodyVM.hpp>
#include <abyss/params/Actors/CodeZero/Param.hpp>

#include <abyss/controllers/Actors/CodeZero/Head/HeadActor.hpp>
#include <abyss/controllers/Actors/CodeZero/Hand/HandActor.hpp>
#include <abyss/controllers/World/World.hpp>

#include <abyss/models/Actors/Commons/CustomColliderModel.hpp>
#include <abyss/models/Actors/Commons/CustomDrawModel.hpp>
#include <abyss/debugs/Log/Log.hpp>

namespace abyss::CodeZero
{
    CodeZeroActor::CodeZeroActor(const CodeZeroEntity& entity):
        EnemyActor(entity.pos, entity.forward),
        m_view(std::make_shared<Body::BodyVM>())
    {
        {
            m_hp->setHp(Param::Base::Hp);
        }
        {
            m_body->noneResistanced();
        }
        {
            (m_state = this->attach<StateModel<CodeZeroActor>>(this))
                ->add<Phase1State>(State::Phase1)
                .add<Phase2State>(State::Phase2)
                .add<Phase3State>(State::Phase3)
                ;
        }
        {
            // コライダーを使用しないので削除
            this->detach<CustomColliderModel>();
        }
        {
            this->attach<PatternModel>(this);
        }
        {
            // デバッグでライフ表示 UIができるまで
#if ABYSS_DEBUG
            this->attach<CustomDrawModel>()->setDrawer([this] {
                Debug::Log::Print << m_hp->value();
            });
#endif
        }
        m_order = -99;
    }

    void CodeZeroActor::start()
    {
        auto* const world = this->m_pManager->getModule<World>();
        m_head = world->create<Head::HeadActor>(this);
        m_leftHand = world->create<Hand::HandActor>(this, Hand::HandActor::Left);
        m_rightHand = world->create<Hand::HandActor>(this, Hand::HandActor::Right);
    }

    bool CodeZeroActor::accept(const ActVisitor& visitor)
    {
        return visitor.visit(*this);
    }

    Body::BodyVM* CodeZeroActor::getBindedView() const
    {
        return &m_view->setPos(m_body->getPos());
    }

    //void CodeZeroActor::onDead()
    //{
    //    // todo
    //    //this->destroy();
    //    //m_head->destroy();
    //    //m_leftHand->destroy();
    //    //m_rightHand->destroy();
    //}

    bool CodeZeroActor::isShotCharge() const
    {
        return m_leftHand->isShotCharge() || m_rightHand->isShotCharge();
    }

}
