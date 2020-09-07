#pragma once
#include <Siv3D/Fwd.hpp>
#include <abyss/components/base/IComponent.hpp>

namespace abyss::Actor::Player::Shot
{
	/// <summary>
	/// Player Shot type
	/// </summary>
	enum class PlayerShotType : s3d::uint8
	{
		Normal,
		Small,
		Medium,
		Big,
	};

	class PlayerShot : public IComponent
	{
		PlayerShotType m_type;
	public:
		PlayerShot(double charge);

		s3d::int32 toPower()const;
		double toRadius() const;
		s3d::ColorF toColorF() const;

		bool operator > (const PlayerShotType& type);
		bool operator >= (const PlayerShotType& type);

		bool isNormal()const;
		bool isSmall()const;
		bool isMedium()const;
		bool isBig()const;

	};
}