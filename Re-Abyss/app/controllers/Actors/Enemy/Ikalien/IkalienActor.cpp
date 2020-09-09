#include "IkalienActor.hpp"
#include <abyss/components/Actors/Enemy/Ikalien/State/WaitState.hpp>

#include <abyss/entities/Actors/Enemy/IkalienEntity.hpp>
#include <abyss/params/Actors/Enemy/Ikalien/Param.hpp>
#include <abyss/types/CShape.hpp>

#include <abyss/controllers/Actors/Enemy/EnemyBuilder.hpp>

namespace
{
    class ViewBinder;
}

namespace abyss::Actor::Enemy::Ikalien
{
    IkalienActor::IkalienActor(const IkalienEntity& entity)
    {
        Enemy::EnemyBuilder builder(this);
        builder
            .setInitPos(entity.pos)
            .setBodyPivot(Param::Base::Pivot)
            .setForward(entity.forward)
            .setInitHp(Param::Base::Hp)
            .setColliderFunc([this] {
                return this->getCollider();
            })
            .setIsEnableMapCollider(false)
            .setAudioSettingGroupPath(U"Enemy/Ikalien/ikalien.aase")
            .setInitState<WaitState>()
            .build();

        {
            m_body->noneResistanced();
        }
        {
            this->attach<RotateModel>();
        }
        {
            this->attach<ViewCtrl<IkalienVM>>()
                ->createBinder<ViewBinder>(this);
        }
    }
    CShape IkalienActor::getCollider() const
    {
        return s3d::Circle(m_body->getPivotPos(), Param::Base::ColRadius);
    }
    bool IkalienActor::accept(const ActVisitor & visitor)
    {
        return visitor.visit(*this);
    }
}

namespace
{
    using namespace abyss;
    using namespace abyss::Actor;
    using namespace abyss::Actor::Enemy::Ikalien;

    class ViewBinder : public ViewCtrl<IkalienVM>::IBinder
    {
        IActor* m_pActor = nullptr;
        Ref<BodyModel> m_body;
        Ref<HPModel> m_hp;
        Ref<RotateModel> m_rotate;

        std::unique_ptr<IkalienVM> m_view;
    private:
        IkalienVM* bind() const final
        {
            return &m_view->setTime(m_pActor->getDrawTimeSec())
                .setPos(m_body->getPos())
                .setVelocity(m_body->getVelocity())
                .setRotate(m_rotate->getRotate())
                .setIsDamaging(m_hp->isInInvincibleTime());
        }
        void setup() final
        {
            m_body = m_pActor->find<BodyModel>();
            m_hp = m_pActor->find<HPModel>();
            m_rotate = m_pActor->find<RotateModel>();
        }
    public:
        ViewBinder(IActor* pActor) :
            m_pActor(pActor),
            m_view(std::make_unique<IkalienVM>())
        {}
    };
}
