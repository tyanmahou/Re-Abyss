#include "Builder.hpp"
#include <abyss/modules/Actor/base/ActorObj.hpp>

#include <abyss/components/Actor/Common/Body.hpp>
#include <abyss/components/Actor/Enemy/CommonBuilder.hpp>
#include <abyss/components/Actor/Enemy/KingDux/BabyDux/ParentObserver.hpp>

namespace
{
	class ViewBinder;
}

namespace abyss::Actor::Enemy::KingDux::BabyDux
{
	void Builder::Build(ActorObj* pActor, ActorObj* parent, const BuildDesc& desc)
	{
        // 共通ビルド
        auto parentBody = parent->find<Body>();
        auto pos = parentBody->getPos() + desc.posOffset;
        CommonBuilder::Build(pActor, BuildOption{}
            .setInitPos(pos)
            //.setBodyPivot(Param::Base::Pivot)
            .setForward(parentBody->getForward())
            //.setInitHp(Param::Base::Hp)
            //.setCollider<MainCollider>(pActor)
            .setIsEnableMapCollider(false)
            .setAudioSettingGroupPath(U"Enemy/KingDux/baby_dux.aase")
            //.setInitState<WaitState>()
            //.setVModelBinder<ViewBinder>(pActor)
        );

        // Body調整
        {
            pActor->find<Body>()->noneResistanced();
        }
		// 親監視
		{
			pActor->attach<ParentObserver>(pActor, parent);
		}
	}
}
