#pragma once
#include <Siv3D/Effect.hpp>
#include <Siv3D/Vector2D.hpp>
#include <Siv3D/HSV.hpp>
#include <abyss/commons/Fwd.hpp>

namespace abyss::Actor::Player::Shot
{
	struct ShotEffect : s3d::IEffect
	{
	private:
		s3d::Vec2 m_pos;
		s3d::HSV m_hsv;
		double m_r;
		Light* m_pLight;
	public:
		ShotEffect(const s3d::Vec2& pos, double r, const s3d::Color& color, Light* pLight = nullptr);

		bool update(double t) override;
	};

	struct ShotFiringEffect : s3d::IEffect
	{
	private:
		s3d::Vec2 m_pos;
		s3d::Color m_color;
		double m_r;
	public:
		ShotFiringEffect(const s3d::Vec2& pos, double r, const s3d::Color& color);

		bool update(double t) override;
	};
}