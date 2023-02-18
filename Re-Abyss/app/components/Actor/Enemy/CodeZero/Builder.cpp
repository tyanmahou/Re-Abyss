#include <abyss/components/Actor/Enemy/CodeZero/Builder.hpp>

#include <abyss/commons/Constants.hpp>
#include <abyss/entities/Actor/Enemy/CodeZeroEntity.hpp>
#include <abyss/params/Actor/Enemy/CodeZero/Param.hpp>

#include <abyss/components/Actor/Common/BehaviorTest.hpp>
#include <abyss/components/Actor/Common/Body.hpp>
#include <abyss/components/Actor/Common/BossFadeMask.hpp>
#include <abyss/components/Actor/Common/BossFadeHider.hpp>
#include <abyss/components/Actor/Common/VModel.hpp>
#include <abyss/components/Actor/Common/ColorCtrl.hpp>
#include <abyss/components/Actor/Common/ColCtrl.hpp>
#include <abyss/components/Actor/Common/Collider.hpp>
#include <abyss/components/Actor/Common/Col/Collider/CircleCollider.hpp>
#include <abyss/components/Actor/Common/Col/Extension/Receiver.hpp>
#include <abyss/components/Actor/Common/ColorAnim/BossDeadColor.hpp>
#include <abyss/components/Actor/Common/ColorAnim/DamageColor.hpp>
#include <abyss/components/Actor/Enemy/BuilderFromEntity.hpp>
#include <abyss/components/Actor/Enemy/CommonBuilder.hpp>
#include <abyss/components/Actor/Enemy/BossHpBarTarget.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/Behavior.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/HeadCtrl.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/EyeCtrl.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/PartsCtrl.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/DeadCallback.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/HideCtrl.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/WingCtrl.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/State/WaitState.hpp>

#include <abyss/views/Actor/Enemy/CodeZero/Body/BodyVM.hpp>
#include <abyss/views/Actor/Enemy/CodeZero/Head/HeadVM.hpp>
#include <abyss/views/Actor/Enemy/CodeZero/Head/EyeVM.hpp>
#include <Siv3D.hpp>

namespace
{
    class Presenter;
}
namespace abyss::Actor::Enemy::CodeZero
{
    void Builder::Build(ActorObj* pActor, const CodeZeroEntity& entity)
    {
        CommonBuilder::Build(pActor, BuildOption{}
            .setInitPos(entity.pos)
            .setBodySize(Vec2{680, 480})
            .setForward(entity.forward)
            .setInitHp(Param::Base::Hp)
            .setIsEnableCollider(false)
            .setIsEnableMapCollider(false)
            .setUseInvincibleColor(true)
            .setIsEnableDeadCallback(false)
            .setIsEnableBreathing(false)
            .setIsEnableItemDrop(false)
            .setIsAutoDestroy(false)
            .setInitState<WaitState>()
            .setVModelPresenter<Presenter>(pActor)
        );

        // Body調整
        {
            pActor->find<Actor::Body>()->noneResistanced();
        }
        // パーツ制御
        Ref<ILocator> headLocator;
        {
            auto head = pActor->attach<HeadCtrl>(pActor);
            headLocator = RefCast<ILocator>(head);
            pActor->attach<PartsCtrl>(pActor);

            pActor->attach<EyeCtrl>(pActor);

            pActor->attach<WingCtrl>(pActor);
        }
        // 衝突
        {
            auto collider = pActor->attach<Collider>();
            collider->add<Col::CircleCollider>(pActor, headLocator)
                ->setRadius(Param::Head::ColRadius);

            pActor->attach<ColCtrl>(pActor)
                ->addBranch()
                ->addNode<Col::Node>(collider->main())
                .setLayer(ColSys::LayerGroup::Enemy)
                .attach<Col::Receiver>(pActor);
        }
        // 行動パターン
        {
            pActor->attach<BehaviorCtrl>(pActor)
                ->setSequence(BehaviorSequence::Root)
                ;

#if ABYSS_DEBUG
            using std::placeholders::_1;
            pActor->attach<BehaviorTest>(pActor)
                ->setInitializer(Behavior::TryToAppear)
                .setWaitAction(Behavior::Wait)
                .registAction(U"LeftAttack", Behavior::LeftAttack)
                .registAction(U"RightAttack", Behavior::RightAttack)
                .registAction(U"BothAttack", Behavior::BothAttack)
                .registAction(U"ChangeHandsPhase1", std::bind(Behavior::ChangeHandsPhase1, _1, false))
                .registAction(U"ChangeHandsPhase2", std::bind(Behavior::ChangeHandsPhase2, _1, false))
                .registAction(U"ChargeShot", Behavior::ChargeShot)
                .registAction(U"RollingAttack", std::bind(Behavior::RollingAttack, _1, false))
                .registAction(U"RollingAttack-R", std::bind(Behavior::RollingAttack, _1, true))
                .registAction(U"Phase2", Behavior::Phase2)
                .registAction(U"Phase3", Behavior::Phase3)
                .registAction(U"Appear", Behavior::Appear)
                .registAction(U"Angry", Behavior::Angry)
                .registAction(U"Dead", Behavior::Dead)
                ;
#endif
        }
        // HPバー検索
        {
            pActor->attach<BossHpBarTarget>(pActor);
        }
        // 死亡時制御
        {
            pActor->attach<DeadCallback>(pActor);
        }
        // 描画制御
        {
            pActor->find<VModel>()->setLayer(DrawLayer::Land)
                .setOrder(DrawOrder::World::MostBack);

            pActor->find<ColorCtrl>()->resizeBuffer(4, 2);
            pActor->find<ColorAnim::DamageColor>()
                ->setIndexMaskMul(0x4);

            // ボス撃破カラー
            pActor->attach<ColorAnim::BossDeadColor>(pActor)
                ->setIndexMaskMul(0x1);

            pActor->attach<HideCtrl>(pActor)
                ->setLayer(DrawLayer::DecorBack)
                .setOrder(DrawOrder::DecorBack::MostFront);

            pActor->attach<BossFadeMask>(pActor)
                ->setDrawer<BossFadeMaskFromMainVModel>(pActor);
            pActor->attach<BossFadeHider>(pActor);
        }
    }
}

namespace
{
    using namespace abyss;
    using namespace abyss::Actor;
    using namespace abyss::Actor::Enemy::CodeZero;

    using abyss::Actor::Enemy::CodeZero::Body::BodyVM;

    class Presenter final : public IVModelPresenterBase
    {
    public:
        Presenter(Actor::ActorObj* pActor) :
            m_pActor(pActor),
            m_viewBody(std::make_unique<BodyVM>()),
            m_viewHead(std::make_unique<Head::HeadVM>()),
            m_viewEye(std::make_unique<Head::EyeVM>()),
            m_rt(Constants::GameScreenSize.asPoint())
        {}
    public:
        void onStart() override
        {
            m_body = m_pActor->find<Actor::Body>();
            m_wing = m_pActor->find<WingCtrl>();

            m_head = m_pActor->find<HeadCtrl>();
            m_eye = m_pActor->find<EyeCtrl>();

            m_colorCtrl = m_pActor->find<ColorCtrl>();
        }
        void onDraw() const override
        {
            {
                m_rt.clear(ColorF(0, 0));
                s3d::ScopedRenderTarget2D renderStart(m_rt);
                s3d::ScopedRenderStates2D blend(BlendState{
                    true,
                    Blend::SrcAlpha,
                    Blend::InvSrcAlpha,
                    BlendOp::Add,
                    Blend::One,
                    Blend::One,
                    BlendOp::Max
                    });
                this->bindBody()->draw();
                this->bindHead()->draw();
            }
            {
                // Viewport 決め打ち
                s3d::ScopedViewport2D viewport{ Constants::GameScreenSize.asPoint() - Point{0, 80} };

                Transformer2D transLocal(Mat3x2::Identity(), Transformer2D::Target::SetLocal);
                Transformer2D transCamera(Mat3x2::Identity(), Transformer2D::Target::SetCamera);
                m_rt.draw(m_colorCtrl->colorMul());
            }

            if (m_eye->isVisible()) {
                this->bindEye()->draw();
            }
        }
    private:
        BodyVM* bindBody() const
        {
            auto pos = m_body->getPos();
            return &m_viewBody->setPos(pos)
                .setWingLPos(pos + m_wing->localL())
                .setWingRPos(pos + m_wing->localR())
                .setColorMul(m_colorCtrl->colorMul(1));
        }

        Head::HeadVM* bindHead() const
        {
            return &m_viewHead->setTime(m_pActor->getTimeSec())
                .setPos(m_head->getPos())
                .setLook(m_head->getLook())
                .setColorMul(m_colorCtrl->colorMul(2))
                .setColorAdd(m_colorCtrl->colorAdd())
                ;
        }

        Head::EyeVM* bindEye() const
        {
            return &m_viewEye
                ->setPos(m_head->getPos())
                .setScale(m_eye->scale())
                .setColorMul(m_colorCtrl->colorMul(3))
                .setColorAdd(m_colorCtrl->colorAdd(1))
                ;
        }
    private:
        ActorObj* m_pActor = nullptr;
        Ref<Actor::Body> m_body;
        Ref<WingCtrl> m_wing;

        Ref<HeadCtrl> m_head;
        Ref<EyeCtrl> m_eye;

        Ref<ColorCtrl> m_colorCtrl;
        std::unique_ptr<BodyVM> m_viewBody;
        std::unique_ptr<Head::HeadVM> m_viewHead;
        std::unique_ptr<Head::EyeVM> m_viewEye;

        s3d::RenderTexture m_rt;
    };
}

namespace abyss::Actor::Enemy
{
    template struct BuilderFromEntity<EnemyType::CodeZero>;
    template<>
    void BuilderFromEntity<EnemyType::CodeZero>::Build(ActorObj* pActor, const EnemyEntity& entity)
    {
        CodeZero::Builder::Build(pActor, static_cast<const CodeZeroEntity&>(entity));
    }
}

