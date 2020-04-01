#pragma once
#include <memory>
#include <Siv3D/Texture.hpp>
#include <Siv3D/Rectangle.hpp>

namespace abyss
{

	class TexturePacker
	{
		struct Frame;
	public:
		class Texture;
	private:
		class Impl;
		std::shared_ptr<Impl> pImpl;
	public:
		TexturePacker() = default;
		TexturePacker(const s3d::FilePath& json);
		TexturePacker(const s3d::Texture& texture, const s3d::FilePath& json);

		TexturePacker::Texture operator()(const s3d::String& fileName)const;
	};

	class TexturePacker::Texture
	{
		friend class TexturePacker;
	private:
		s3d::Texture m_texture;
		const Frame& m_frame;

		s3d::RectF m_uvRect;
		s3d::Vec2 m_size;
		double m_angle;
		s3d::Vec2 m_center;
	private:
		Texture(const s3d::Texture& texture, const Frame& frame);
	public:

		TexturePacker::Texture& operator()(const s3d::Vec2& pos, const s3d::Vec2& size);

		TexturePacker::Texture& resized(const s3d::Vec2& size);

		TexturePacker::Texture& scaled(double scale);
		TexturePacker::Texture& scaled(const s3d::Vec2& scale);
		TexturePacker::Texture& scaled(double sx, double sy);

		const TexturePacker::Texture& rotated(double angle);
		const TexturePacker::Texture& rotatedAt(double x, double y, double angle);
		const TexturePacker::Texture& rotatedAt(const s3d::Vec2& pos, double angle);

		s3d::Quad draw(double x, double y, const s3d::ColorF& diffuse = s3d::Palette::White) const;

		s3d::Quad draw(const s3d::Vec2& pos, const s3d::ColorF& diffuse = s3d::Palette::White) const;

		s3d::Quad drawAt(double x, double y, const s3d::ColorF& diffuse = s3d::Palette::White) const;

		s3d::Quad drawAt(const s3d::Vec2& pos, const s3d::ColorF& diffuse = s3d::Palette::White) const;
	};

}