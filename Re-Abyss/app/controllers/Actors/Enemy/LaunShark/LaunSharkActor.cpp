#include "LaunSharkActor.hpp"

#include <abyss/components/Actors/Enemy/LaunShark/State/SwimState.hpp>
#include <abyss/entities/Actors/Enemy/LaunSharkEntity.hpp>
#include <abyss/params/Actors/Enemy/LaunShark/Param.hpp>

#include <abyss/components/Actors/Commons/TimeCounter.hpp>
#include <abyss/controllers/Actors/Enemy/EnemyBuilder.hpp>

namespace
{
    class ViewBinder;
}
namespace abyss::Actor::Enemy::LaunShark
{
    LaunSharkActor::LaunSharkActor(const LaunSharkEntity& entity)
    {
        Enemy::EnemyBuilder builder(this);

        builder
            .setInitPos(entity.pos)
            .setForward(entity.forward)
            .setBodySize(Param::Base::Size)
            .setInitHp(Param::Base::Hp)
            .setIsEnableRoomHit(true, true)
            .setAudioSettingGroupPath(U"Enemy/LaunShark/laun_shark.aase")
            .setInitState<SwimState>()
            .build();

        {
            m_body
                ->noneResistanced();
        }
        {
            this->attach<TimeCounter>();
        }
        {
            this->attach<ViewCtrl<LaunSharkVM>>()
                ->createBinder<ViewBinder>(this);
        }
    }
    
    bool LaunSharkActor::accept(const ActVisitor& visitor)
    {
        return visitor.visit(*this);
    }
}

namespace
{
    using namespace abyss;
    using namespace abyss::Actor;
    using namespace abyss::Actor::Enemy::LaunShark;

    class ViewBinder : public ViewCtrl<LaunSharkVM>::IBinder
    {
        IActor* m_pActor = nullptr;
        Ref<Body> m_body;
        Ref<HP> m_hp;
        std::unique_ptr<LaunSharkVM> m_view;
    private:
        LaunSharkVM* bind() const final
        {
            return &m_view->setTime(m_pActor->getDrawTimeSec())
                .setPos(m_body->getPos())
                .setForward(m_body->getForward())
                .setIsDamaging(m_hp->isInInvincibleTime());
        }
        void setup() final
        {
            m_body = m_pActor->find<Body>();
            m_hp = m_pActor->find<HP>();
        }
    public:
        ViewBinder(IActor* pActor) :
            m_pActor(pActor),
            m_view(std::make_unique<LaunSharkVM>())
        {}
    };
}