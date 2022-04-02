#include <abyss/views/Effect/Actor/Common/EnemyDeadVM.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>

namespace abyss::Effect::Actor
{
	EnemyDeadVM::EnemyDeadVM():
		m_texture(Resource::Assets::Main()->load(U"Effect/Actor/Common/CommonEffects.json"))
	{}

	EnemyDeadVM& EnemyDeadVM::setPos(const s3d::Vec2& pos)
	{
		m_pos = pos;
		return *this;
	}
	EnemyDeadVM& EnemyDeadVM::setAnimRate(double animeRate)
	{
		m_animeRate = animeRate;
		return *this;
	}
	void EnemyDeadVM::draw() const
	{
		const auto frame = static_cast<int32>(m_animeRate * 6.0);
		m_texture(U"enemy_dead")(40 * frame, 0, 40, 40).drawAt(m_pos);
	}
}
