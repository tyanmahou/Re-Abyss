#include "Builder.hpp"

#include <abyss/modules/Actors/base/ActorObj.hpp>

#include <abyss/entities/Actors/Enemy/IkalienEntity.hpp>
#include <abyss/params/Actors/Enemy/Ikalien/Param.hpp>
#include <abyss/types/CShape.hpp>

#include <abyss/components/Actors/Commons/HP.hpp>
#include <abyss/components/Actors/Enemy/CommonBuilder.hpp>
#include <abyss/components/Actors/Enemy/Ikalien/State/WaitState.hpp>


namespace
{
    class Collider;
    class ViewBinder;
}

namespace abyss::Actor::Enemy::Ikalien
{
    void Builder::Build(ActorObj* pActor, const IkalienEntity& entity)
    {
        // 共通ビルド
        CommonBuilder::Build(pActor, BuildOption{}
            .setInitPos(entity.pos)
            .setBodyPivot(Param::Base::Pivot)
            .setForward(entity.forward)
            .setInitHp(Param::Base::Hp)
            .setColliderImpl<Collider>(pActor)
            .setIsEnableMapCollider(false)
            .setAudioSettingGroupPath(U"Enemy/Ikalien/ikalien.aase")
            .setInitState<WaitState>()
        );

        // Body調整
        {
            pActor->find<Body>()->noneResistanced();
        }
        // 回転制御
        {
            pActor->attach<RotateCtrl>();
        }
        // 描画
        {
            pActor->attach<ViewCtrl<IkalienVM>>()
                ->createBinder<ViewBinder>(pActor);
        }
    }
}

namespace
{
    using namespace abyss;
    using namespace abyss::Actor;
    using namespace abyss::Actor::Enemy::Ikalien;

    class Collider final : public CustomCollider::IImpl
    {
    public:
        Collider(ActorObj* pActor) :
            m_pActor(pActor)
        {}

        void onStart() override
        {
            m_body = m_pActor->find<Body>();
        }
        CShape getCollider() const override
        {
            return s3d::Circle(m_body->getPivotPos(), Param::Base::ColRadius);
        }
    private:
        ActorObj* m_pActor = nullptr;
        Ref<Body> m_body;
    };

    class ViewBinder : public ViewCtrl<IkalienVM>::IBinder
    {
        ActorObj* m_pActor = nullptr;
        Ref<Body> m_body;
        Ref<HP> m_hp;
        Ref<RotateCtrl> m_rotate;

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
        void onStart() final
        {
            m_body = m_pActor->find<Body>();
            m_hp = m_pActor->find<HP>();
            m_rotate = m_pActor->find<RotateCtrl>();
        }
    public:
        ViewBinder(ActorObj* pActor) :
            m_pActor(pActor),
            m_view(std::make_unique<IkalienVM>())
        {}
    };
}
