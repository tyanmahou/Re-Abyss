#include "Generator.hpp"

#include <abyss/modules/Manager/Manager.hpp>
#include <abyss/modules/Camera/Camera.hpp>
#include <abyss/modules/GlobalTime/GlobalTime.hpp>
#include <abyss/modules/Effect/Effects.hpp>
#include <abyss/modules/Effect/base/EffectObj.hpp>
#include <abyss/modules/Room/RoomManager.hpp>

#include <abyss/components/Effect/Bubble/Builder.hpp>
#include <abyss/components/Effect/Bubble/Main.hpp>
#include <abyss/utils/Coro/Task/Task.hpp>
#include <abyss/utils/Coro/Wait/Wait.hpp>
#include <Siv3D/Array.hpp>

namespace abyss::Cron::BubbleGenerator
{
	Generator::Generator(Manager* pManager):
		m_pManager(pManager)
	{}
	void Generator::onStart()
	{
		s3d::Array<Ref<Effect::EffectObj>> objs;
		for (int sec = 0; sec <= 30; sec += 1) {
			if (auto effect = this->buildEffect()) {
				objs << effect;
			}
		}
		auto* pCamera = m_pManager->getModule<Camera>();
		for (size_t index = 0; index < objs.size(); ++index) {
			double sec = static_cast<double>(index) + 5.0;
			auto& obj = objs[index];
			obj->updateDeltaTime(sec);
			obj->update();
			if (!obj->find<Effect::Bubble::Main>()->isInArea(pCamera->screenRegion())) {
				// スクリーン内じゃなければ消す
				obj->destroy();
			}
		}
	}
	Coro::Task<> Generator::onExecute()
    {
		auto time = m_pManager->getModule<GlobalTime>();
		auto clock = [time] {return time->timeMicroSec(); };

		this->buildEffect();
		co_yield Coro::WaitForSecondsEx(0.1s, clock);
		this->buildEffect();
		co_yield Coro::WaitForSecondsEx(0.1s, clock);
		this->buildEffect();
		co_return;
    }
	void Generator::onCheckOut()
	{
		const auto& next = m_pManager->getModule<RoomManager>()->nextRoom();
		if (!next) {
			return;
		}
		s3d::Array<Ref<Effect::EffectObj>> objs;
		for (int sec = 0; sec <= 30; sec += 1) {
			if (auto effect = this->buildEffect(next->getRegion())) {
				objs << effect;
			}
		}
		auto* pCamera = m_pManager->getModule<Camera>();
		for (size_t index = 0; index < objs.size(); ++index) {
			double sec = static_cast<double>(index) + 5.0;

			auto& obj = objs[index];
			obj->updateDeltaTime(sec);
			obj->update();
			auto main = obj->find<Effect::Bubble::Main>();
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

		using Effect::Bubble::BubbleKind;
		using Effect::Bubble::LayerKind;
		m_count = ++m_count % 6;
		switch (m_count) {
		case 0: return effects->createDecorFront<Effect::Bubble::Builder>(BubbleKind::Middle, LayerKind::Front, area);
		case 1: return effects->createDecorFront<Effect::Bubble::Builder>(BubbleKind::Small, LayerKind::Middle, area);
		case 2: return effects->createDecorBack<Effect::Bubble::Builder>(BubbleKind::Big, LayerKind::Back, area);
		case 3: return effects->createDecorFront<Effect::Bubble::Builder>(BubbleKind::Big, LayerKind::Front, area);
		case 4: return effects->createDecorFront<Effect::Bubble::Builder>(BubbleKind::Small, LayerKind::Middle, area);
		case 5: return effects->createDecorBack<Effect::Bubble::Builder>(BubbleKind::Middle, LayerKind::Back, area);
		}
		return nullptr;
	}
}

