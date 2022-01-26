#pragma once
#include <Siv3D/Vector2D.hpp>
#include <Siv3D/Texture.hpp>
#include <Siv3D/Optional.hpp>

namespace abyss
{
	class BackGroundVM
	{
		s3d::Texture m_texture;
		s3d::Vec2 m_offset;

		s3d::Vector2D<bool> m_fix;
		s3d::Vector2D<s3d::Optional<double>> m_rate;
	public:
		BackGroundVM(
			const s3d::String& path,
			const s3d::Vec2& offset,
			const s3d::Vector2D<bool>& fix,
			const s3d::Vector2D<s3d::Optional<double>>& rate
		);
		BackGroundVM(const BackGroundVM& other);
		void draw(const s3d::Vec2& pos)const;
	};
}