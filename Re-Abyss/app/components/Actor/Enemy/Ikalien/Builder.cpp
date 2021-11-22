#include "Builder.hpp"

#include <abyss/modules/Actor/base/ActorObj.hpp>

#include <abyss/entities/Actor/Enemy/IkalienEntity.hpp>
#include <abyss/params/Actor/Enemy/Ikalien/Param.hpp>
#include <abyss/types/CShape.hpp>

#include <abyss/components/Actor/Common/DamageCtrl.hpp>
#include <abyss/components/Actor/Common/VModel.hpp>
#include <abyss/components/Actor/Enemy/CommonBuilder.hpp>
#include <abyss/components/Actor/Enemy/Ikalien/State/WaitState.hpp>
#include <abyss/components/Actor/Enemy/Ikalien/MainCollider.hpp>

#include <abyss/views/Actor/Enemy/Ikalien/IkalienVM.hpp>

namespace
{
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
            .setCollider<MainCollider>(pActor)
            .setIsEnableMapCollider(false)
            .setAudioSettingGroupPath(U"Enemy/Ikalien/ikalien.aase")
            .setInitState<WaitState>()
            .setVModelBinder<ViewBinder>(pActor)
        );

        // Body調整
        {
            pActor->find<Body>()->noneResistanced();
        }
        // 回転制御
        {
            pActor->attach<RotateCtrl>();
        }
    }
}

namespace
{
    using namespace abyss;
    using namespace abyss::Actor;
    using namespace abyss::Actor::Enemy::Ikalien;

    class ViewBinder : public IVModelBinder<IkalienVM>
    {
        ActorObj* m_pActor = nullptr;
        Ref<Body> m_body;
        Ref<DamageCtrl> m_damage;
        Ref<RotateCtrl> m_rotate;
        Ref<MotionCtrl> m_motion;

        std::unique_ptr<IkalienVM> m_view;
    private:
        IkalienVM* bind() const final
        {
            return &m_view->setTime(m_pActor->getTimeSec())
                .setPos(m_body->getPos())
                .setVelocity(m_body->getVelocity())
                .setRotate(m_rotate->getRotate())
                .setIsDamaging(m_damage->isInInvincibleTime())
                .setMotion(m_motion->get<Motion>())
                ;
        }
        void onStart() final
        {
            m_body = m_pActor->find<Body>();
            m_damage = m_pActor->find<DamageCtrl>();
            m_rotate = m_pActor->find<RotateCtrl>();
            m_motion = m_pActor->find<MotionCtrl>();
        }
    public:
        ViewBinder(ActorObj* pActor) :
            m_pActor(pActor),
            m_view(std::make_unique<IkalienVM>())
        {}
    };
}
