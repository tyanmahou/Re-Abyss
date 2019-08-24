#pragma once
#include <Siv3D/Fwd.hpp>
#include <memory>

namespace abyss
{

	class TexturePacker
	{
		class Impl;
		std::shared_ptr<Impl> pImpl;
	public:
		TexturePacker() = default;
		TexturePacker(const s3d::FilePath& json);
		TexturePacker(const s3d::Texture& texture, const s3d::FilePath& json);

		s3d::TextureRegion operator()(const s3d::String& fileName)const;
		s3d::TextureRegion operator()(const s3d::String& fileName, const s3d::Vec2& pos, const s3d::Vec2& size)const;
	};
}