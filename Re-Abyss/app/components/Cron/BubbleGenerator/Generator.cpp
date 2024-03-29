#include <abyss/components/Cron/BubbleGenerator/Generator.hpp>

#include <abyss/modules/Manager/Manager.hpp>
#include <abyss/modules/Camera/Camera.hpp>
#include <abyss/modules/GlobalTime/GlobalTime.hpp>
#include <abyss/modules/Effect/Effects.hpp>
#include <abyss/modules/Effect/base/EffectObj.hpp>
#include <abyss/modules/Room/RoomManager.hpp>

#include <abyss/components/Effect/Misc/Bubble/Builder.hpp>
#include <abyss/components/Effect/Misc/Bubble/Main.hpp>
#include <abyss/utils/Coro/Fiber/Fiber.hpp>
#include <abyss/utils/Coro/Fiber/FiberUtil.hpp>
#include <Siv3D/Array.hpp>

namespace
{
	constexpr double period = 0.4;
}

namespace abyss::Cron::BubbleGenerator
{
	Generator::Generator(Manager* pManager):
		m_pManager(pManager)
	{}
	void Generator::onStart()
	{
		s3d::Array<Ref<Effect::EffectObj>> objs;
		for (double sec = 0; sec <= 20; sec += period) {
			objs << this->buildEffect();
		}
		auto* pCamera = m_pManager->getModule<Camera>();
		auto* pRoomManager = m_pManager->getModule<RoomManager>();
		for (size_t index = 0; index < objs.size(); ++index) {
			auto& obj = objs[index];
			if (!obj) {
				continue;
			}
			double sec = static_cast<double>(index) * period + 5.0;
			obj->updateDeltaTime(sec);
			obj->update();
			auto area = pRoomManager ? pRoomManager->currentRoom().getRegion() : pCamera->screenRegion();
			if (!obj->find<Effect::Misc::Bubble::Main>()->isInArea(area)) {
				// スクリーン内じゃなければ消す
				obj->destroy();
			}
		}
	}
	Coro::Fiber<> Generator::onExecute()
    {
		auto time = m_pManager->getModule<GlobalTime>();
		while (true) {
			this->buildEffect();
			co_await Coro::FiberUtil::WaitForSeconds(s3d::Duration(period), time);
		}
		co_return;
    }
	void Generator::onCheckOut()
	{
		const auto& next = m_pManager->getModule<RoomManager>()->nextRoom();
		if (!next) {
			return;
		}
		s3d::Array<Ref<Effect::EffectObj>> objs;
		for (double sec = 0; sec <= 20; sec += period) {
			objs << this->buildEffect(next->getRegion());
		}
		auto* pCamera = m_pManager->getModule<Camera>();
		for (size_t index = 0; index < objs.size(); ++index) {
			auto& obj = objs[index];
			if (!obj) {
				continue;
			}
			double sec = static_cast<double>(index) * period + 5.0;
			obj->updateDeltaTime(sec);
			obj->update();
			auto main = obj->find<Effect::Misc::Bubble::Main>();
			if (main->isInArea(pCamera->screenRegion())) {
				// 現在のスクリーン内ならば消す
				obj->destroy();
			} else if (!main->isInArea(next->getRegion())) {
				// 次の部屋に入ってないなら消す
				obj->destroy();
			}
		}
	}
	void Generator::onCheckIn()
	{
	
	}
	Ref<Effect::EffectObj> Generator::buildEffect(const s3d::Optional<s3d::RectF>& area)
	{
		auto effects = m_pManager->getModule<Effects>();

		using namespace Effect::Misc;
		using Bubble::BubbleKind;
		using Bubble::LayerKind;
		m_count = ++m_count % 36;
		if (s3d::int32 layer = m_count % 3; layer == 0) {
			if (m_count % 6 == 0) {
				return effects->createDecorFront<Bubble::Builder>(BubbleKind::Middle, LayerKind::Front, area);
			} else {
				return effects->createDecorFront<Bubble::Builder>(BubbleKind::Big, LayerKind::Front, area);
			}
		} else if (layer == 1) {
			if (m_count % 9 == 1) {
				return effects->createWorldFront<Bubble::Builder>(BubbleKind::Small, LayerKind::Middle, area);
			}
		} else {
			if (m_count % 12 == 2) {
				return effects->createDecorBack<Bubble::Builder>(BubbleKind::Big, LayerKind::Back, area);
			} else if (m_count % 12 == 8) {
				return effects->createDecorBack<Bubble::Builder>(BubbleKind::Middle, LayerKind::Back, area);
			}
		}
		return nullptr;
	}
}

