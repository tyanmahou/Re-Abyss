#pragma once
#include <memory>
#include <Siv3D/Texture.hpp>
#include <Siv3D/RectF.hpp>

namespace abyss
{

	class TexturePacker
	{
	private:
		struct Frame;
		class Impl;
		std::shared_ptr<Impl> pImpl;
	public:
		TexturePacker() = default;
		TexturePacker(const s3d::FilePath& json);
		TexturePacker(const s3d::Image& image, const s3d::FilePath& json);

		[[nodiscard]] bool isContain(const s3d::String& fileName) const;
		[[nodiscard]] Texture operator()(const s3d::String& fileName)const;
		[[nodiscard]] explicit operator bool()const;
	};
}