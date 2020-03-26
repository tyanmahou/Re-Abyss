#pragma once
#include <Siv3D/Fwd.hpp>

namespace abyss
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

	class PlayerShotModel
	{
		PlayerShotType m_type;
	public:
		PlayerShotModel(double charge);

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