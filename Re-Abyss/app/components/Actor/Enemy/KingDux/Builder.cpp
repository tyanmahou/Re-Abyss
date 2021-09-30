#include "Builder.hpp"
#include <abyss/modules/Actor/base/ActorObj.hpp>

#include <abyss/components/Actor/Common/DamageCtrl.hpp>
#include <abyss/components/Actor/Common/Body.hpp>
#include <abyss/components/Actor/Common/VModel.hpp>

#include <abyss/components/Actor/Enemy/CommonBuilder.hpp>
#include <abyss/components/Actor/Enemy/KingDux/EyeCtrl.hpp>


#include <abyss/params/Actor/Enemy/KingDux/Param.hpp>
#include <abyss/views/Actor/Enemy/KingDux/KingDuxVM.hpp>
#include <abyss/views/Actor/Enemy/KingDux/Foot/FootVM.hpp>

namespace
{
    class ViewBinder;
    class ViewBinderFoot;
}

namespace abyss::Actor::Enemy::KingDux
{
    void Builder::Build(ActorObj* pActor, const KingDuxEntity& entity)
    {
        // 共通ビルド
        CommonBuilder::Build(pActor, BuildOption{}
            .setInitPos(entity.pos)
            .setBodySize(Param::Base::ColSize)
            .setBodyPivot(Param::Base::Pivot)
            .setForward(entity.forward)
            .setInitHp(Param::Base::Hp)
            //.setColliderImpl<Collider>(pActor)
            .setIsEnableMapCollider(false)
            .setAudioSettingGroupPath(U"Enemy/KingDux/king_dux.aase")
            //.setInitState<WaitState>()
            .setVModelBinder<ViewBinder>(pActor)
        );

        // Body調整
        {
            pActor->find<Body>()->noneResistanced();
        }
        // 目制御
        {
            pActor->attach<EyeCtrl>(pActor);
        }
        {
            pActor->find<VModel>()
                ->setLayer(DrawLayer::WorldBack);

            pActor->attach<VModelSub<1>>()
                ->setBinder<ViewBinderFoot>(pActor, Param::Foot::PosR)
                .setLayer(DrawLayer::BackGround);

            pActor->attach<VModelSub<2>>()
                ->setBinder<ViewBinderFoot>(pActor, Param::Foot::PosL, Param::Foot::AnimTimeSec / 2.0)
                .setLayer(DrawLayer::WorldFront);

            pActor->attach<VModelSub<3>>()
                ->setBinder<ViewBinderFoot>(pActor, s3d::Vec2{250, 0}, Param::Foot::AnimTimeSec / 3.0)
                .setLayer(DrawLayer::DecorMiddle);

            pActor->attach<VModelSub<4>>()
                ->setBinder<ViewBinderFoot>(pActor, s3d::Vec2{ -200, -100 }, Param::Foot::AnimTimeSec / 4.0, true)
                .setLayer(DrawLayer::BackGround);
        }
    }
}

namespace
{
    using namespace abyss;
    using namespace abyss::Actor;
    using namespace abyss::Actor::Enemy::KingDux;
    using namespace abyss::Actor::Enemy::KingDux::Foot;

    class ViewBinder : public IVModelBinder<KingDuxVM>
    {
    public:
        ViewBinder(ActorObj* pActor) :
            m_pActor(pActor),
            m_view(std::make_unique<KingDuxVM>())
        {}
    private:
        KingDuxVM* bind() const final
        {
            return &m_view->setTime(m_pActor->getTimeSec())
                .setPos(m_body->getPos())
                .setEyePos(m_eye->getEyePosL(), m_eye->getEyePosR())
                .setIsDamaging(m_damage->isInInvincibleTime())
                ;
        }
        void onStart() final
        {
            m_body = m_pActor->find<Body>();
            m_damage = m_pActor->find<DamageCtrl>();
            m_eye = m_pActor->find<EyeCtrl>();
        }
    private:
        ActorObj* m_pActor = nullptr;
        Ref<Body> m_body;
        Ref<DamageCtrl> m_damage;
        Ref<EyeCtrl> m_eye;

        std::unique_ptr<KingDuxVM> m_view;
    };

    class ViewBinderFoot : public IVModelBinder<FootVM>
    {
    public:
        ViewBinderFoot(ActorObj* pActor, const s3d::Vec2& offset, double timeOffset = 0, bool isFlip = false) :
            m_pActor(pActor),
            m_view(std::make_unique<FootVM>()),
            m_offset(offset),
            m_timeOffset(timeOffset),
            m_isFlip(isFlip)
        {}
    private:
        void setup(Executer executer) final
        {
            executer.on<IDraw>().addAfter<VModel>();
        }
        FootVM* bind() const final
        {
            return &m_view->setTime(m_pActor->getTimeSec() + m_timeOffset)
                .setPos(m_body->getPos() + m_offset)
                .setIsDamaging(m_damage->isInInvincibleTime())
                .setIsFlip(m_isFlip)
                ;
        }
        void onStart() final
        {
            m_body = m_pActor->find<Body>();
            m_damage = m_pActor->find<DamageCtrl>();
        }
    private:
        ActorObj* m_pActor = nullptr;
        Ref<Body> m_body;
        Ref<DamageCtrl> m_damage;

        std::unique_ptr<FootVM> m_view;
        s3d::Vec2 m_offset;
        double m_timeOffset = 0;
        bool m_isFlip = false;
    };
}