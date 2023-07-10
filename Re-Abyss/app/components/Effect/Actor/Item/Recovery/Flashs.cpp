#include <abyss/components/Effect/Actor/Item/Recovery/Flashs.hpp>
#include <abyss/modules/Effect/base/EffectObj.hpp>
#include <abyss/utils/TimeLite/Timer.hpp>

namespace abyss::Effect::Actor::Item::Recovery
{
	Flashs::Flash::Flash()
	{
		m_localPos = RandomBool() ?
			RandomVec2(Rect{ -30, 0, 15, 30 }) :
			RandomVec2(Rect{ 15, 0, 15, 30 });
	}

	bool Flashs::Flash::update(const s3d::Vec2& pos, double dt)
	{
		m_lifeTime += dt;
		auto rate = m_lifeTime / 0.2;
		auto alpha = (0.2 - m_lifeTime) / m_lifeTime;
		Line(pos + m_localPos + Vec2{ 0, -5 } *rate, pos + m_localPos + Vec2{ 0, -50 } *rate).draw(2.0, ColorF(1.0, alpha));
		return m_lifeTime <= 0.2;
	}

	Flashs::Flashs(EffectObj* pObj):
		m_pObj(pObj)
	{
		m_task.reset(std::bind(&Flashs::updateAsync, this));
	}

	Coro::Fiber<void> Flashs::updateAsync()
	{
		for ([[maybe_unused]] auto count : step(1, 10)) {
			m_flashs.emplace_back();

			TimeLite::Timer timer{ 0.1 };
			while (!timer.isEnd()) {
				timer.update(m_pObj->deltaTime());
				co_yield{};
			}
		}
	}

	void Flashs::onStart()
	{
		m_location = m_pObj->find<LocationCtrl>();
	}

	bool Flashs::onDraw([[maybe_unused]]double time)
	{
		ScopedRenderStates2D blend(BlendState::Additive);

		const auto& pos = m_location->getPos();
		double dt = m_pObj->deltaTime();

		for (auto it = m_flashs.begin(); it != m_flashs.end();) {
			if (!it->update(pos, dt)) {
				it = m_flashs.erase(it);
			} else {
				++it;
			}
		}

		return m_task.resume();
	}
}
