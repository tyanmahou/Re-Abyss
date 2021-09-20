#include "TexturePacker.hpp"
#include <Siv3D.hpp>
#include <Siv3D/JSON.hpp>
#include <Siv3D/String.hpp>
#include <Siv3D/FileSystem.hpp>
#include <Siv3D/Texture.hpp>
#include <Siv3D/TextureRegion.hpp>
#include <Siv3D/Vector2D.hpp>
#include <abyss/utils/FileUtil/FileUtil.hpp>

#include<unordered_map>

using namespace s3d;

namespace abyss
{
	struct TexturePacker::Frame
	{
		String filename;
		Size pos;
		Size size;
		Size spriteSourcePos;
		Size spriteSourceSize;
		Size sourceSize;

		bool rotated;
	};
	class TexturePacker::Impl
	{
		s3d::Image m_image;
		std::unordered_map<String, Frame> m_frames;
		std::unordered_map<String, Texture> m_textures;

		void load(const s3d::FilePath& json)
		{
			JSON reader = JSON::Load(json);
			if (!reader) {
				return;
			}
			for (const auto& elm : reader[U"frames"].arrayView()) {
				Frame info;
				info.filename = elm[U"filename"].getString();
				{
					const auto& frame = elm[U"frame"];
					info.pos = {
						frame[U"x"].get<int32>(),
						frame[U"y"].get<int32>(),
					};
					info.size = {
						frame[U"w"].get<int32>(),
						frame[U"h"].get<int32>(),
					};
				}
				{
					const auto& source = elm[U"spriteSourceSize"];
					info.spriteSourcePos = {
						source[U"x"].get<int32>(),
						source[U"y"].get<int32>(),
					};
					info.spriteSourceSize = {
						source[U"w"].get<int32>(),
						source[U"h"].get<int32>(),
					};
				}
				{
					const auto& source = elm[U"sourceSize"];
					info.sourceSize = {
						source[U"w"].get<int32>(),
						source[U"h"].get<int32>(),
					};
				}
				info.rotated = elm[U"rotated"].get<bool>();

				m_frames[FileSystem::BaseName(info.filename)] = info;
			}
			if (!m_image) {
				FilePath parent = FileUtil::ParentPath(json);
				auto imagePath = reader[U"meta.image"].getString();
				m_image = s3d::Image(parent + imagePath);
			}
		}
		s3d::Texture create(const s3d::String& fileName)
		{
			if (m_frames.find(fileName) == m_frames.end()) {
				return s3d::Texture();
			}
			const Frame& frame = m_frames.at(fileName);
			Image image(frame.sourceSize, ColorF(0, 0));

			size_t endX = frame.spriteSourcePos.x + frame.spriteSourceSize.x;
			size_t endY = frame.spriteSourcePos.y + frame.spriteSourceSize.y;
			for (size_t y = frame.spriteSourcePos.y; y < endY; ++y) {
				size_t srcY = y - frame.spriteSourcePos.y;
				for (size_t x = frame.spriteSourcePos.x; x < endX; ++x) {
					size_t srcX = x - frame.spriteSourcePos.x;

					auto tmpX = !frame.rotated ? srcX : (frame.size.y - 1) - srcY;
					auto tmpY = !frame.rotated ? srcY : srcX;
					image[y][x] = m_image[tmpY + frame.pos.y][tmpX + frame.pos.x];
				}
			}
			return s3d::Texture(image);
		}
	public:
		Impl(const s3d::FilePath& json)
		{
			this->load(json);
		}


		Impl(const s3d::Image& image, const s3d::FilePath& json):
			m_image(image)
		{
			this->load(json);
		}

		bool isContain(const s3d::String& fileName) const
		{
			return m_frames.find(fileName) != m_frames.end();
		}

		Texture operator()(const s3d::String& fileName)
		{
			if (m_textures.find(fileName) != m_textures.end()) {
				return m_textures[fileName];
			}
			return m_textures[fileName] = this->create(fileName);
		}
		explicit operator bool()const
		{
			return !m_image.isEmpty() && !m_frames.empty();
		}
	};
	TexturePacker::TexturePacker(const s3d::FilePath& json):
		pImpl(std::make_shared<Impl>(json))
	{
	}
	TexturePacker::TexturePacker(const s3d::Image& image, const s3d::FilePath& json) :
		pImpl(std::make_shared<Impl>(image, json))
	{
	}
	bool TexturePacker::isContain(const s3d::String& fileName) const
	{
		return pImpl->isContain(fileName);
	}
	Texture TexturePacker::operator()(const s3d::String& fileName) const
	{
		return (*pImpl)(fileName);
	}

    TexturePacker::operator bool() const
    {
		return static_cast<bool>(*pImpl);
	}
}