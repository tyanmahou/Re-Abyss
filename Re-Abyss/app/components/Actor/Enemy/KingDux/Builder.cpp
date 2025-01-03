﻿#include <abyss/components/Actor/Enemy/KingDux/Builder.hpp>

#include <abyss/modules/Actor/base/ActorObj.hpp>

#include <abyss/components/Actor/Common/DamageCtrl.hpp>
#include <abyss/components/Actor/Common/Body.hpp>
#include <abyss/components/Actor/Common/BehaviorTest.hpp>
#include <abyss/components/Actor/Common/ShakeCtrl.hpp>
#include <abyss/components/Actor/Common/VModel.hpp>
#include <abyss/components/Actor/Common/VModelUpdater.hpp>
#include <abyss/components/Actor/Common/ColCtrl.hpp>
#include <abyss/components/Actor/Common/Collider.hpp>
#include <abyss/components/Actor/Common/Col/Extension/Attacker.hpp>
#include <abyss/components/Actor/Common/Col/Extension/Receiver.hpp>
#include <abyss/components/Actor/Common/ColorCtrl.hpp>
#include <abyss/components/Actor/Common/TerrainProxy.hpp>

#include <abyss/components/Actor/Enemy/BuilderFromEntity.hpp>
#include <abyss/components/Actor/Enemy/CommonBuilder.hpp>
#include <abyss/components/Actor/Enemy/MidBossDeadCtrl.hpp>
#include <abyss/components/Actor/Enemy/KingDux/BabyCtrl.hpp>
#include <abyss/components/Actor/Enemy/KingDux/EyeCtrl.hpp>
#include <abyss/components/Actor/Enemy/KingDux/Behavior.hpp>
#include <abyss/components/Actor/Enemy/KingDux/State/WaitState.hpp>
#include <abyss/components/Actor/Enemy/KingDux/KingDuxUtil.hpp>
#include <abyss/components/Actor/Enemy/KingDux/MainCollider.hpp>
#include <abyss/components/Actor/Enemy/KingDux/CrownCollider.hpp>
#include <abyss/components/Actor/Enemy/KingDux/DeadCallback.hpp>

#include <abyss/params/Actor/Enemy/KingDux/Param.hpp>
#include <abyss/views/Actor/Enemy/KingDux/KingDuxVM.hpp>
#include <abyss/views/Actor/Enemy/KingDux/Foot/FootVM.hpp>

#include <Siv3D.hpp>

namespace
{
    class Presenter;
    class PresenterFoot;
}

namespace abyss::Actor::Enemy::KingDux
{
    void Builder::Build(ActorObj* pActor, const KingDuxEntity& entity)
    {
        // 共通ビルド
        CommonBuilder::Build(pActor, BuildOption{}
            .setDeployId(entity.id)
            .setInitPos(entity.pos)
            .setBodySize(Param::Base::ColSize)
            .setBodyOffset(Param::Base::Pivot)
            .setForward(entity.forward)
            .setInitHp(Param::Base::Hp)
            .setCollider<MainCollider>(pActor)
            .setIsEnableMapCollider(false)
            .setIsEnableItemDrop(false)
            .setUseInvincibleColor(true)
            .setIsEnableDeadCallback(false)
            .setIsAutoDestroy(false)
            .setInitState<WaitState>()
            .setVModelPresenter<Presenter>(pActor)
        );

        // 中ボス制御
        {
            pActor->attach<MidBossDeadCtrl>(pActor);
        }

        // Body調整
        {
            pActor->find<Body>()->noneResistanced();
        }
        // Shake
        {
            pActor->attach<ShakeCtrl>(pActor);
        }
        // Behavior
        {
            pActor->attach<BehaviorCtrl>(pActor)
                ->setSequence(BehaviorSequence::Root);
#if ABYSS_DEBUG
            pActor->attach<BehaviorTest>(pActor)
                ->setWaitAction(Behavior::Wait)
                .registAction(U"Stab", Behavior::Stab)
                .registAction(U"Stab2", Behavior::Stab2)
                .registAction(U"Stab3", Behavior::Stab3)
                .registAction(U"PursuitStab", Behavior::PursuitStab)
                .registAction(U"Convene", Behavior::Convene)
                .registAction(U"Appear", Behavior::Appear)
                .registAction(U"Angry", Behavior::Angry)
                .registAction(U"Dead", Behavior::Dead)
                ;
#endif
        }

        // 目制御
        {
            pActor->attach<EyeCtrl>(pActor);
        }

        // 衝突
        {
            auto crownCollider = pActor->find<Collider>()
                ->add<CrownCollider>(pActor);

            pActor->find<ColCtrl>()
                ->addBranch()
                ->addNode<Col::Node>(RefCast<Col::ICollider>(crownCollider))
                .setLayer(ColSys::LayerGroup::Enemy)
                .attach<Col::Attacker>(pActor, 1)
                .attach<Col::Receiver>(pActor);
        }
        // 地形扱い
        {
            pActor->attach<TerrainProxy>(pActor)
                ->setColDirection(ColDirection::All)
                .setRegion(Param::Base::Terrain.movedBy(entity.pos))
                ;
        }

        // Baby制御
        {
            pActor->attach<BabyCtrl>(pActor);
        }

        // 死亡時制御
        {
            pActor->attach<DeadCallback>(pActor);
        }
        // 描画
        {
            pActor->find<VModel>()
                ->setLayer(DrawLayer::WorldBack);

            pActor->attach<VModelSub<1>>()
                ->setPresenter<PresenterFoot>(pActor, Param::Foot::Foot1)
                .setLayer(DrawLayer::DecorBack);

            pActor->attach<VModelSub<2>>()
                ->setPresenter<PresenterFoot>(pActor, Param::Foot::Foot2)
                .setLayer(DrawLayer::WorldFront);

            pActor->attach<VModelSub<3>>()
                ->setPresenter<PresenterFoot>(pActor, Param::Foot::Foot3)
                .setLayer(DrawLayer::Land);

            pActor->attach<VModelSub<4>>()
                ->setPresenter<PresenterFoot>(pActor, Param::Foot::Foot4)
                .setLayer(DrawLayer::DecorBack);

            pActor->attach<VModelUpdater>(pActor);
        }

        // 初期設定
        {
            KingDuxUtil::SetVisible(pActor, false);
        }
    }
}

namespace
{
    using namespace abyss;
    using namespace abyss::Actor;
    using namespace abyss::Actor::Enemy::KingDux;
    using namespace abyss::Actor::Enemy::KingDux::Foot;

    class Presenter : public IVModelPresenter<KingDuxVM>
    {
    public:
        Presenter(ActorObj* pActor) :
            m_pActor(pActor),
            m_view(std::make_unique<KingDuxVM>())
        {}
    private:
        KingDuxVM* bind() const final
        {
            return &m_view->setTime(m_modelUpdater->getTime())
                .setAnimTime(m_motion->animeTime())
                .setPos(m_body->getPos() + m_shake->getShakeOffset())
                .setEyePos(m_eye->getEyePosL(), m_eye->getEyePosR())
                .setIsDamaging(m_damage->isInvincibleTime())
                .setColorMul(m_colorCtrl->colorMul())
                .setColorAdd(m_colorCtrl->colorAdd())
                .setMotion(m_motion->get<Motion>())
                ;
        }
        void onStart() final
        {
            m_body = m_pActor->find<Body>();
            m_shake = m_pActor->find<ShakeCtrl>();
            m_damage = m_pActor->find<DamageCtrl>();
            m_eye = m_pActor->find<EyeCtrl>();
            m_motion = m_pActor->find<MotionCtrl>();
            m_modelUpdater = m_pActor->find<VModelUpdater>();
            m_colorCtrl = m_pActor->find<ColorCtrl>();
        }
    private:
        ActorObj* m_pActor = nullptr;
        Ref<Body> m_body;
        Ref<ShakeCtrl> m_shake;
        Ref<DamageCtrl> m_damage;
        Ref<EyeCtrl> m_eye;
        Ref<MotionCtrl> m_motion;
        Ref<VModelUpdater> m_modelUpdater;
        Ref<ColorCtrl> m_colorCtrl;
        std::unique_ptr<KingDuxVM> m_view;
    };

    class PresenterFoot : public IVModelPresenter<FootVM>
    {
    public:
        PresenterFoot(ActorObj* pActor, const FootDesc& desc) :
            m_pActor(pActor),
            m_view(std::make_unique<FootVM>()),
            m_offset(desc.pos),
            m_timeOffset(desc.animTimeOffset),
            m_isFlip(desc.isFlip),
            m_rotate(s3d::ToRadians(desc.rotateDeg))
        {}
    private:
        void setup(Executer executer) final
        {
            executer.on<IDraw>().addAfter<VModel>();
        }
        FootVM* bind() const final
        {
            return &m_view->setTime(m_modelUpdater->getTime() + m_timeOffset)
                .setAnimTime(m_motion->animeTime())
                .setPos(m_body->getPos() + m_offset)
                .setIsFlip(m_isFlip)
                .setRotate(m_rotate)
                .setColorMul(m_colorCtrl->colorMul())
                .setColorAdd(m_colorCtrl->colorAdd())
                .setMotion(m_motion->get<Motion>())
                ;
        }
        void onStart() final
        {
            m_body = m_pActor->find<Body>();
            m_damage = m_pActor->find<DamageCtrl>();
            m_modelUpdater = m_pActor->find<VModelUpdater>();
            m_motion = m_pActor->find<MotionCtrl>();
            m_colorCtrl = m_pActor->find<ColorCtrl>();
        }
    private:
        ActorObj* m_pActor = nullptr;
        Ref<Body> m_body;
        Ref<DamageCtrl> m_damage;
        Ref<VModelUpdater> m_modelUpdater;
        Ref<MotionCtrl> m_motion;
        Ref<ColorCtrl> m_colorCtrl;

        std::unique_ptr<FootVM> m_view;
        s3d::Vec2 m_offset;
        double m_timeOffset = 0;
        bool m_isFlip = false;
        double m_rotate = 0;
    };
}

namespace abyss::Actor::Enemy
{
    template struct BuilderFromEntity<EnemyType::KingDux>;
    template<>
    void BuilderFromEntity<EnemyType::KingDux>::Build(ActorObj* pActor, const EnemyEntity& entity)
    {
        KingDux::Builder::Build(pActor, static_cast<const KingDuxEntity&>(entity));
    }
}
