#include "CaptainTakoActor.hpp"

#include <abyss/entities/Actors/Enemy/CaptainTakoEntity.hpp>
#include <abyss/models/Actors/Enemy/CaptainTako/State/WaitState.hpp>
#include <abyss/params/Actors/Enemy/CaptainTako/Param.hpp>

#include <abyss/controllers/Actors/Enemy/EnemyBuilder.hpp>

namespace
{
    class ViewBinder;
}
namespace abyss::CaptainTako
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
            this->attach<ViewModel<CaptainTakoVM>>()
                ->createBinder<ViewBinder>(this);
        }
    }
    bool CaptainTakoActor::accept(const ActVisitor & visitor)
    {
        return visitor.visit(*this);
    }
}

namespace
{
    using namespace abyss;
    using namespace abyss::CaptainTako;

    class ViewBinder : public ViewModel<CaptainTakoVM>::IBinder
    {
        IActor* m_pActor = nullptr;
        Ref<BodyModel> m_body;
        Ref<HPModel> m_hp;
    private:
        CaptainTakoVM* bind(CaptainTakoVM* view) const
        {
            return &view
                ->setTime(m_pActor->getDrawTimeSec())
                .setPos(m_body->getPos())
                .setForward(m_body->getForward())
                .setIsDamaging(m_hp->isInInvincibleTime());
        }
        void setup() override
        {
            m_body = m_pActor->find<BodyModel>();
            m_hp = m_pActor->find<HPModel>();
        }
    public:
        ViewBinder(IActor* pActor) :
            m_pActor(pActor)
        {}
    };
}
