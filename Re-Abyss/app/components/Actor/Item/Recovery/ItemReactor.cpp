#include <abyss/components/Actor/Item/Recovery/ItemReactor.hpp>

#include <abyss/components/Actor/Common/ILocator.hpp>
#include <abyss/components/Actor/Common/HP.hpp>
#include <abyss/components/Actor/Common/AudioSource.hpp>
#include <abyss/params/Actor/Item/Recovery/Param.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/modules/Temporary/Temporary.hpp>
#include <abyss/modules/Effect/Effects.hpp>
#include <abyss/views/Actor/Item/Recovery/RecoveryEffect.hpp>

namespace
{
    using namespace abyss::Actor::Item;
    using namespace abyss::Actor::Item::Recovery;

    s3d::int32 RecoveryValue(RecoveryKind kind)
    {
        switch (kind) {
        case RecoveryKind::Small:
            return Param::Small.recoveryValue;
        case RecoveryKind::Middle:
            return Param::Middle.recoveryValue;
        case RecoveryKind::Big:
            return Param::Big.recoveryValue;
        }
        return 0;
    }
}
namespace abyss::Actor::Item::Recovery
{
    ItemReactor::ItemReactor(ActorObj* pActor, RecoveryKind kind, const s3d::Optional<s3d::uint32>& objId) :
        m_pActor(pActor),
        m_kind(kind),
        m_objId(objId)
    {}
    void ItemReactor::onStart()
    {
        if (m_objId) {
            // 取得済みなら破棄
            if (m_pActor->getModule<Temporary>()->onFlag(TempKey::ItemGet(*m_objId))) {
                m_pActor->destroy();
                return;
            }
        }
        m_shake = m_pActor->find<ShakeCtrl>();
    }
    void ItemReactor::onUpdate()
    {
        m_isCollide = m_isCollideNext;
        m_isCollideNext = false;
    }
    void ItemReactor::onGained(ActorObj* player)
    {
        m_isCollideNext = true;
        auto playerHp = player->find<HP>();
        if (!playerHp || playerHp->isFull()) {
            if (!m_isCollide && m_shake) {
                // あたったばかりならシェイク
                m_shake->request();
            }
            return;
        }
        // 破棄
        m_pActor->destroy();

        if (m_objId) {
            // IDありならリスタートレベルの保存する
            m_pActor->getModule<Temporary>()->saveFlagRestart(TempKey::ItemGet(*m_objId));
        }

        m_pActor->getModule<Effects>()->createWorldFront<RecoveryEffect>(player->find<ILocator>());
        m_pActor->find<AudioSource>()->playAt(U"Gained");
        // 体力回復
        playerHp->heal(::RecoveryValue(m_kind));
    }
}
