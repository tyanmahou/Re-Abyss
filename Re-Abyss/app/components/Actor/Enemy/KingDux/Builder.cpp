#include "Builder.hpp"
#include <abyss/modules/Actor/base/ActorObj.hpp>

#include <abyss/components/Actor/Common/HP.hpp>
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
                ->setBinder<ViewBinderFoot>(pActor, s3d::Vec2{ -500, 400 - 90 })
                .setLayer(DrawLayer::BackGround);

            pActor->attach<VModelSub<2>>()
                ->setBinder<ViewBinderFoot>(pActor, s3d::Vec2{100, 400 - 90}, 0.5)
                .setLayer(DrawLayer::WorldFront);
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
            return &m_view->setTime(m_pActor->getDrawTimeSec())
                .setPos(m_body->getPos())
                .setEyePos(m_eye->getEyePosL(), m_eye->getEyePosR())
                .setIsDamaging(m_hp->isInInvincibleTime())
                ;
        }
        void onStart() final
        {
            m_body = m_pActor->find<Body>();
            m_hp = m_pActor->find<HP>();
            m_eye = m_pActor->find<EyeCtrl>();
        }
    private:
        ActorObj* m_pActor = nullptr;
        Ref<Body> m_body;
        Ref<HP> m_hp;
        Ref<EyeCtrl> m_eye;

        std::unique_ptr<KingDuxVM> m_view;
    };

    class ViewBinderFoot : public IVModelBinder<FootVM>
    {
    public:
        ViewBinderFoot(ActorObj* pActor, const s3d::Vec2& offset, double timeOffset = 0) :
            m_pActor(pActor),
            m_view(std::make_unique<FootVM>()),
            m_offset(offset),
            m_timeOffset(timeOffset)
        {}
    private:
        FootVM* bind() const final
        {
            return &m_view->setTime(m_pActor->getDrawTimeSec() + m_timeOffset)
                .setPos(m_body->getPos() + m_offset)
                .setIsDamaging(m_hp->isInInvincibleTime())
                ;
        }
        void onStart() final
        {
            m_body = m_pActor->find<Body>();
            m_hp = m_pActor->find<HP>();
        }
    private:
        ActorObj* m_pActor = nullptr;
        Ref<Body> m_body;
        Ref<HP> m_hp;

        std::unique_ptr<FootVM> m_view;
        s3d::Vec2 m_offset;
        double m_timeOffset = 0;
    };
}