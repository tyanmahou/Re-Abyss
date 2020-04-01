#include "TexturePacker.hpp"
#include<Siv3D.hpp>
#include <Siv3D/JSONReader.hpp>
#include <Siv3D/String.hpp>
#include <Siv3D/FileSystem.hpp>
#include <Siv3D/Texture.hpp>
#include <Siv3D/TextureRegion.hpp>
#include <Siv3D/Vector2D.hpp>

#include<unordered_map>

using namespace s3d;

namespace abyss
{
	struct TexturePacker::Frame
	{
		String filename;
		Vec2 pos;
		Vec2 size;

		bool rotated;
	};
	class TexturePacker::Impl
	{
		s3d::Texture m_texture;
		std::unordered_map<String, Frame> m_frames;

		void load(const s3d::FilePath& json)
		{
			JSONReader reader(json);
			if (!reader) {
				return;
			}
			for (const auto& elm : reader[U"frames"].arrayView()) {
				Frame info;
				info.filename = elm[U"filename"].getString();
				const auto& frame = elm[U"frame"];
				info.pos = {
					frame[U"x"].get<double>(),
					frame[U"y"].get<double>(),
				};
				info.size = {
					frame[U"w"].get<double>(),
					frame[U"h"].get<double>(),
				};
				info.rotated = elm[U"rotated"].get<bool>();

				m_frames[FileSystem::BaseName(info.filename)] = info;
			}
			if (!m_texture) {
				const FilePath& parent = FileSystem::ParentPath(json);
				auto imagePath = reader[U"meta.image"].getString();
				m_texture = s3d::Texture(parent + imagePath);
			}
		}
	public:
		Impl(const s3d::FilePath& json)
		{
			this->load(json);
		}


		Impl(const s3d::Texture& texture, const s3d::FilePath& json):
			m_texture(texture)
		{
			this->load(json);
		}

		TexturePacker::Texture operator()(const s3d::String& fileName) const
		{
			const Frame& frame = m_frames.at(fileName);
			return Texture(m_texture, frame);
		}
	};
	TexturePacker::TexturePacker(const s3d::FilePath& json):
		pImpl(std::make_shared<Impl>(json))
	{
	}
	TexturePacker::TexturePacker(const s3d::Texture& texture, const s3d::FilePath& json) :
		pImpl(std::make_shared<Impl>(texture, json))
	{
	}
	TexturePacker::Texture TexturePacker::operator()(const s3d::String& fileName) const
	{
		return (*pImpl)(fileName);
	}
	
	TexturePacker::Texture::Texture(const s3d::Texture& texture, const Frame& frame):
		m_texture(texture),
		m_frame(frame),
		m_uvRect({0, 0}, frame.size),
		m_size(frame.size),
		m_angle(0),
		m_center(frame.size / 2.0)
	{}

	TexturePacker::Texture& TexturePacker::Texture::operator()(const s3d::Vec2 & pos, const s3d::Vec2 & size)
	{
		m_uvRect.set(pos, size);
		m_size = m_uvRect.size;
		m_center = m_size / 2.0;

		return *this;
	}
	TexturePacker::Texture& TexturePacker::Texture::resized(const s3d::Vec2& size)
	{
		m_size = size;
		m_center = m_size / 2;
	}
	TexturePacker::Texture& TexturePacker::Texture::scaled(double scale)
	{
		return this->scaled(scale, scale);
	}
	TexturePacker::Texture& TexturePacker::Texture::scaled(const s3d::Vec2& scale)
	{
		return this->scaled(scale.x, scale.y);
	}
	TexturePacker::Texture& TexturePacker::Texture::scaled(double sx, double sy)
	{
		m_size.x *= sx;
		m_size.y *= sy;

		m_center = m_size / 2.0;
		return *this;
	}
	TexturePacker::Texture& TexturePacker::Texture::rotated(double angle)
	{
		m_angle = angle;
		return *this;
	}
	TexturePacker::Texture& TexturePacker::Texture::rotatedAt(double x, double y, double angle)
	{
		return this->rotatedAt({ x, y }, angle);
	}
	TexturePacker::Texture& TexturePacker::Texture::rotatedAt(const s3d::Vec2& pos, double angle)
	{
		m_center = pos;
		return this->rotated(angle);
	}
#define FIX_PARAM \
	auto uvRect = m_frame.rotated ? RectF{\
	    m_frame.size.y - m_uvRect.pos.y - m_uvRect.size.y,\
	    m_uvRect.pos.x,\
	    m_uvRect.size.y,\
	    m_uvRect.size.x\
	} : m_uvRect;\
	auto size = m_frame.rotated ? Vec2{ m_size.y, m_size.x } : m_size;\
	auto center = m_frame.rotated ? Vec2{ m_size.y - m_center.y, m_center.x } : m_center;\
	auto angle = m_frame.rotated ? m_angle - Math::Constants::HalfPi : m_angle;

	s3d::Quad TexturePacker::Texture::draw(double x, double y, const s3d::ColorF& diffuse) const
	{
		FIX_PARAM

		return m_texture(m_frame.pos + uvRect.pos, uvRect.size)
			.resized(size)
			.rotatedAt(center, angle)
			.draw(x, y, diffuse);
	}
	s3d::Quad TexturePacker::Texture::draw(const s3d::Vec2& pos, const s3d::ColorF& diffuse) const
	{
		return this->draw(pos.x, pos.y, diffuse);
	}
	s3d::Quad TexturePacker::Texture::drawAt(double x, double y, const s3d::ColorF& diffuse) const
	{
		FIX_PARAM

		return m_texture(m_frame.pos + uvRect.pos, uvRect.size)
			.resized(size)
			.rotatedAt(center, angle)
			.drawAt(x, y, diffuse);
	}
	s3d::Quad TexturePacker::Texture::drawAt(const s3d::Vec2& pos, const s3d::ColorF& diffuse) const
	{
		return this->drawAt(pos.x, pos.y, diffuse);
	}
}