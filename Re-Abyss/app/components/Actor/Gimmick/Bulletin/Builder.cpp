#include "Builder.hpp"
#include <abyss/components/Actor/Commons/CustomDraw.hpp>
#include <abyss/components/Actor/Commons/Locator.hpp>
#include <abyss/components/Actor/Commons/Colliders/CircleCollider.hpp>
#include <abyss/components/Actor/Gimmick/Bulletin/Talkable.hpp>
#include <abyss/views/Actor/Gimmick/Bulletin/BulletinVM.hpp>

namespace
{
	class Drawer;
}

namespace abyss::Actor::Gimmick::Bulletin
{
    void Builder::Build(ActorObj* pActor, const BulletinEntity& entity)
    {
		pActor->setDestoryTiming(DestoryTiming::CheckIn);

		// 座標
		{
			pActor->attach<Locator>()
				->setPos(entity.pos);
		}

		// コライダー
		{
			pActor->attach<CircleCollider>(pActor)
				->setRadius(30.0);
		}

		// 会話制御
		{
			pActor->attach<Talkable>(pActor, entity.event);
		}

		// 描画
		{
			pActor->attach<CustomDraw>()
				->setDrawer<Drawer>(pActor)
				.setLayer(DrawLayer::DecorMiddle);
		}
    }
}

namespace
{
	using namespace abyss;
	using namespace abyss::Actor;
	using namespace abyss::Actor::Gimmick::Bulletin;

	class Drawer : public CustomDraw::IImpl
	{
	public:
		Drawer(ActorObj* pActor) :
			m_pActor(pActor),
			m_view(std::make_unique<BulletinVM>())
		{}

		void onStart() override
		{
			m_locator = m_pActor->find<ILocator>();
		}
		void onDraw() const override
		{
			m_view
				->setPos(m_locator->getCenterPos())
				.draw();
		}
	private:
		ActorObj* m_pActor;

		Ref<ILocator> m_locator;
		std::unique_ptr<BulletinVM> m_view;
	};
}