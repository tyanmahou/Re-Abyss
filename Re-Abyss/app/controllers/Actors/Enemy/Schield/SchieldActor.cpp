#include "SchieldActor.hpp"

#include <abyss/models/Actors/Enemy/Schield/State/WaitState.hpp>

#include <abyss/entities/Actors/Enemy/SchieldEntity.hpp>
#include <abyss/params/Actors/Enemy/Schield/Param.hpp>
#include <abyss/models/Actors/Commons/StateModel.hpp>
#include <abyss/models/Actors/Enemy/Schield/DamageModel.hpp>
#include <abyss/models/Actors/Enemy/Schield/FaceCtrlModel.hpp>
#include <abyss/types/CShape.hpp>
#include <abyss/controllers/Actors/Enemy/EnemyBuilder.hpp>

namespace
{
    class ViewBinder;
}
namespace abyss::Actor::Enemy::Schield
{
    SchieldActor::SchieldActor(const SchieldEntity& entity)
    {
        Enemy::EnemyBuilder builder(this);

        builder
            .setInitPos(entity.pos)
            .setForward(entity.forward)
            .setBodySize(Param::Base::Size)
            .setInitHp(Param::Base::Hp)
            .setColliderFunc([this] {
                return this->getCollider();
            })
            .setAudioSettingGroupPath(U"Enemy/Schield/schield.aase")
            .setIsEnableDamage(false)
            .setInitState<WaitState>()
            .build();
        {
            this->attach<DamageModel>(this);
        }
        {
            this->attach<ViewModel<SchieldVM>>()
                ->createBinder<ViewBinder>(this);
        }
        {
            m_face = this->attach<FaceCtrlModel>(this);
        }
    }

    CShape SchieldActor::getCollider() const
    {
        if (m_face->isOnFace()) {
            s3d::Array<CShape> shapes;
            shapes << m_face->getCollider() << m_body->region();
            return shapes;
        }
        return m_body->region();
    }
    bool SchieldActor::accept(const ActVisitor& visitor)
    {
        return visitor.visit(*this);
    }
}

namespace
{
    using namespace abyss;
    using namespace abyss::Actor::Enemy::Schield;

    class ViewBinder : public ViewModel<SchieldVM>::IBinder
    {
        IActor* m_pActor = nullptr;
        Ref<BodyModel> m_body;
        Ref<HPModel> m_hp;

        std::unique_ptr<SchieldVM> m_view;
    private:
        SchieldVM* bind() const final
        {
            return &m_view->setTime(m_pActor->getDrawTimeSec())
                .setPos(m_body->getPos())
                .setForward(m_body->getForward())
                .setIsDamaging(m_hp->isInInvincibleTime())
                ;
        }
        void setup() final
        {
            m_body = m_pActor->find<BodyModel>();
            m_hp = m_pActor->find<HPModel>();
        }
    public:
        ViewBinder(IActor* pActor) :
            m_pActor(pActor),
            m_view(std::make_unique<SchieldVM>())
        {}
    };
}

