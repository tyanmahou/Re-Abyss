#include "Builder.hpp"
#include <abyss/modules/Actor/base/ActorObj.hpp>

#include <abyss/components/Actor/Common/HP.hpp>
#include <abyss/components/Actor/Common/Body.hpp>
#include <abyss/components/Actor/Common/VModel.hpp>

#include <abyss/components/Actor/Enemy/CommonBuilder.hpp>
#include <abyss/components/Actor/Enemy/KingDux/EyeCtrl.hpp>


#include <abyss/params/Actor/Enemy/KingDux/Param.hpp>
#include <abyss/views/Actor/Enemy/KingDux/KingDuxVM.hpp>

namespace
{
    class ViewBinder;
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
        }
    }
}

namespace
{
    using namespace abyss;
    using namespace abyss::Actor;
    using namespace abyss::Actor::Enemy::KingDux;

    class ViewBinder : public IVModelBinder<KingDuxVM>
    {
        ActorObj* m_pActor = nullptr;
        Ref<Body> m_body;
        Ref<HP> m_hp;
        Ref<EyeCtrl> m_eye;

        std::unique_ptr<KingDuxVM> m_view;
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
    public:
        ViewBinder(ActorObj* pActor) :
            m_pActor(pActor),
            m_view(std::make_unique<KingDuxVM>())
        {}
    };
}