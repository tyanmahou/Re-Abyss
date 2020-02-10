#pragma once
#include <type_traits>
#include <Siv3D/Fwd.hpp>


namespace abyss 
{
	struct CollisionPairHash
	{
		s3d::uint64 id1;
		s3d::uint64 id2;

		CollisionPairHash(s3d::uint64 id1, s3d::uint64 id2) :
			id1(id1),
			id2(id2)
		{}
		bool operator ==(const CollisionPairHash& other) const
		{
			return this->id1 == other.id1 && this->id2 == other.id2;
		}
		bool operator !=(const CollisionPairHash& other) const
		{
			return !(*this == other);
		}
	};
}

namespace std 
{
	template<>
	struct hash<abyss::CollisionPairHash>
	{
		size_t operator ()(const abyss::CollisionPairHash& col) const
		{
			s3d::uint64 shift = (col.id2 << 32) | (col.id2 >> 32);
			return static_cast<size_t>(col.id1 ^ shift);
		}
	};
}