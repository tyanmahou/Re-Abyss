#include "CaptainTakoActor.hpp"

#include <abyss/entities/Actors/Enemy/CaptainTakoEntity.hpp>
#include <abyss/components/Actors/Enemy/CaptainTako/State/WaitState.hpp>
#include <abyss/params/Actors/Enemy/CaptainTako/Param.hpp>

#include <abyss/controllers/Actors/Enemy/EnemyBuilder.hpp>

namespace
{
    class ViewBinder;
}
namespace abyss::Actor::Enemy::CaptainTako
{
    CaptainTakoActor::CaptainTakoActor(const CaptainTakoEntity& entity)
    {
        Enemy::EnemyBuilder builder(this);
        builder
            .setInitPos(entity.pos)
            .setForward(entity.forward)
            .setBodySize(Param::Base::Size)
            .setBodyPivot(Param::Base::Pivot)
            .setInitHp(Param::Base::Hp)
            .setAudioSettingGroupPath(U"Enemy/CaptainTako/captain_tako.aase")
            .setInitState<WaitState>()
            .build();

        {
            this->attach<ViewCtrl<CaptainTakoVM>>()
                ->createBinder<ViewBinder>(this);
        }
    }
}

namespace
{
    using namespace abyss;
    using namespace abyss::Actor;
    using namespace abyss::Actor::Enemy::CaptainTako;

    class ViewBinder : public ViewCtrl<CaptainTakoVM>::IBinder
    {
        IActor* m_pActor = nullptr;
        Ref<Body> m_body;
        Ref<HP> m_hp;

        std::unique_ptr<CaptainTakoVM> m_view;
    private:
        CaptainTakoVM* bind() const final
        {
            return &m_view
                ->setTime(m_pActor->getDrawTimeSec())
                .setPos(m_body->getPos())
                .setForward(m_body->getForward())
                .setIsDamaging(m_hp->isInInvincibleTime());
        }
        void onStart() final
        {
            m_body = m_pActor->find<Body>();
            m_hp = m_pActor->find<HP>();
        }
    public:
        ViewBinder(IActor* pActor) :
            m_pActor(pActor),
            m_view(std::make_unique<CaptainTakoVM>())
        {}
    };
}
