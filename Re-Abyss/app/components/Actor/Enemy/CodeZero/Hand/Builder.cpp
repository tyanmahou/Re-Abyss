#include <abyss/components/Actor/Enemy/CodeZero/Hand/Builder.hpp>

#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/params/Actor/Enemy/CodeZero/HandParam.hpp>

#include <abyss/components/Actor/Common/StateCtrl.hpp>
#include <abyss/components/Actor/Common/ShakeCtrl.hpp>
#include <abyss/components/Actor/Common/RotateCtrl.hpp>
#include <abyss/components/Actor/Common/Body.hpp>
#include <abyss/components/Actor/Common/BodyUpdater.hpp>
#include <abyss/components/Actor/Common/BossFadeMask.hpp>
#include <abyss/components/Actor/Common/BossFadeHider.hpp>
#include <abyss/components/Actor/Common/ColorCtrl.hpp>
#include <abyss/components/Actor/Common/VModel.hpp>
#include <abyss/components/Actor/Common/ColCtrl.hpp>
#include <abyss/components/Actor/Common/Collider.hpp>
#include <abyss/components/Actor/Common/Col/Collider/CircleCollider.hpp>
#include <abyss/components/Actor/Common/Col/Extension/Mover.hpp>
#include <abyss/components/Actor/Common/Col/Extension/Attacker.hpp>

#include <abyss/components/Actor/Enemy/CodeZero/ParentCtrl.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/Hand/HandProxy.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/Hand/HandMove.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/Hand/KindCtrl.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/Hand/ShockWaveCtrl.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/Hand/State/PursuitState.hpp>

#include <abyss/views/Actor/Enemy/CodeZero/Hand/HandVM.hpp>
namespace
{
    class Presenter;
}
namespace abyss::Actor::Enemy::CodeZero::Hand
{
    void Builder::Build(ActorObj* pActor, ActorObj* parent, HandKind kind)
    {
        const auto forward = kind == HandKind::Left ? Forward::Left : Forward::Right;

        // Body
        {
            s3d::Vec2 offs = HandParam::Base::InitOffs;
            offs.x = offs.x * forward;
            pActor->attach<Body>(pActor)
                ->initPos(parent->find<Body>()->getPos() + offs)
                .noneResistanced();
            pActor->attach<BodyUpdater>(pActor);
        }
        // 衝突
        {
            auto collider = pActor->attach<Collider>();
            collider->add<Col::CircleCollider>(pActor)
                ->setRadius(HandParam::Base::ColRadius);

            pActor->attach<ColCtrl>(pActor)
                ->addBranch()
                ->addNode<Col::Node>(collider->main())
                .setLayer(ColSys::LayerGroup::Enemy)
                .attach<Col::Mover>(pActor)
                .attach<Col::Attacker>(pActor, 1)
                ;
        }
        // 回転制御
        {
            pActor->attach<RotateCtrl>();
        }
        // ハンド制御
        {
            pActor->attach<HandMove>(pActor);
            pActor->attach<KindCtrl>(kind);
        }
        // 親監視
        {
            pActor->attach<ParentCtrl>(parent);
        }
        // 状態
        {
            constexpr bool slowStart = true;
            auto desc = kind == HandKind::Left ? HandDesc::CreateLeftPhase1() :
                HandDesc::CreateRightPhase1();

            pActor->attach<StateCtrl>(pActor)
                ->changeState<PursuitState>(desc, slowStart);
        }

        // 衝撃波
        {
            pActor->attach<ShockWaveCtrl>(pActor);
        }
        // Shake
        {
            pActor->attach<ShakeCtrl>(pActor);
        }
        // 描画制御
        {
            pActor->attach<MotionCtrl>();
            pActor->attach<VModel>()
                ->setPresenter<Presenter>(pActor, forward);

            pActor->attach<BossFadeMask>(pActor)
                ->setDrawer<BossFadeMaskFromMainVModel>(pActor);
            pActor->attach<BossFadeHider>(pActor);
        }
        // プロキシ
        {
            pActor->attach<HandProxy>(pActor);
        }
    }
}

namespace
{
    using namespace abyss;
    using namespace abyss::Actor;
    using namespace abyss::Actor::Enemy::CodeZero;
    using namespace abyss::Actor::Enemy::CodeZero::Hand;

    class Presenter : public IVModelPresenter<HandVM>
    {
    private:
        HandVM* bind() const final
        {
            return &m_view->setTime(m_pActor->getTimeSec())
                .setPos(m_body->getPos() + m_shake->getShakeOffset())
                .setRotate(m_rotate->getRotate())
                .setMotion(m_motion->get<Motion>())
                .setColorMul(m_colorCtrl->colorMul())
                .setColorAdd(m_colorCtrl->colorAdd())
                ;
        }
        void onStart() final
        {
            m_body = m_pActor->find<Body>();
            m_shake = m_pActor->find<ShakeCtrl>();
            m_rotate = m_pActor->find<RotateCtrl>();
            m_motion = m_pActor->find<MotionCtrl>();
            m_colorCtrl = m_pActor->find<ParentCtrl>()->getParent()->find<ColorCtrl>();
        }
    public:
        Presenter(ActorObj* pActor, Forward forward) :
            m_pActor(pActor),
            m_view(std::make_unique<HandVM>(forward))
        {}
    private:
        ActorObj* m_pActor = nullptr;
        Ref<Body> m_body;
        Ref<ShakeCtrl> m_shake;
        Ref<RotateCtrl> m_rotate;
        Ref<MotionCtrl> m_motion;
        Ref<ColorCtrl> m_colorCtrl;
        std::unique_ptr<HandVM> m_view;
    };
}
