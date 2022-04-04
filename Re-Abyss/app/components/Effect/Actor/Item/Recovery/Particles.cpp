#include <abyss/components/Effect/Actor/Item/Recovery/Particles.hpp>
#include <abyss/modules/Effect/base/EffectObj.hpp>
#include <abyss/components/Effect/Actor/Item/Recovery/ColorDef.hpp>

namespace abyss::Effect::Actor::Item::Recovery
{
	Particles::Particle::Particle(bool isFrame, bool isColor0):
		m_localPos(RandomVec2(Circle(Vec2{ 0, 15 }, 40.0))),
		m_size(Random(4.0, 10.0)),
		m_angle(Random()* Math::TwoPi),
		m_isFrame(isFrame)
	{
		auto hsv = HSV(isColor0 ? Color0 : Color1);
		hsv.s += 0.5;
		m_color = hsv.toColorF();
	}

	bool Particles::Particle::update(const s3d::Vec2& pos, double t)
	{
		constexpr double moveTime = 0.5;
		auto spreadRate = s3d::EaseOutCirc(s3d::Min(t, moveTime) / moveTime);
		auto newPos = pos + m_localPos * spreadRate;
		if (t >= moveTime) {
			newPos += Vec2{ m_localPos.x / 2.0, 0 } *(t - moveTime);
		}
		if (t >= moveTime / 2.0) {
			newPos += Vec2{ 0.0, -50.0 } *(t - moveTime / 2.0);
		}
		{
			auto rotateRate = spreadRate * 5.0;
			if (t >= moveTime) {
				rotateRate += (t - moveTime);
			}
			auto alpha = 1.0;
			if (alpha >= moveTime) {
				alpha = 1.0 - (t - moveTime) / (1.0 - moveTime);
			}
			Vec2 sizeVec2 = Vec2::One() * m_size * (1 - t);
			auto quad = RectF(newPos - sizeVec2 / 2.0, sizeVec2)
				.rotatedAt(newPos, m_angle + s3d::Math::TwoPi * rotateRate);
			if (m_isFrame) {
				quad.draw(m_color);
			} else {
				quad.drawFrame(1, m_color);
			}
		}
		return t <= 1.0;
	}
	Particles::Particles(EffectObj* pObj):
		m_pObj(pObj)
	{
		for (auto count : step(1, 20)) {
			m_particles.emplace_back(count > 10, count % 2 == 0);
		}
	}

	void Particles::onStart()
	{
		m_location = m_pObj->find<LocationCtrl>();
	}

	bool Particles::onDraw(double time)
	{
		ScopedRenderStates2D blend(BlendState::Additive);

		const auto& pos = m_location->getPos();

		bool result = false;
		for (auto&& particle : m_particles) {
			result |= particle.update(pos, time);
		}
		return result;
	}
}