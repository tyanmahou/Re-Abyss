#pragma once
#include <abyss/utils/TexturePacker/TexturePacker.hpp>

namespace abyss
{
	struct KiraKiraEffect : IEffect
	{
	public:
		enum Type
		{
			Type1,
			Type2,
		};
	private:
		Type m_type;
		const s3d::Vec2 m_pos;
		TexturePacker m_texture;
	public:

		KiraKiraEffect(const s3d::Vec2& pos, Type type = Type::Type1);

		bool update(double t)override;
	};
}