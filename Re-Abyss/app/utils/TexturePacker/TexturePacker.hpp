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

		[[nodiscard]] bool isContain(const s3d::String& fileName) const;
		[[nodiscard]] TexturePacker::Texture operator()(const s3d::String& fileName)const;
		[[nodiscard]] explicit operator bool()const;
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

		bool m_mirrored = false;
		bool m_fliped = false;
	private:
		Texture(const s3d::Texture& texture, const Frame& frame);

	public:
		[[nodiscard]] s3d::TexturedQuad getFixedQuad() const;

		[[nodiscard]] TexturePacker::Texture& operator()(const s3d::Vec2& pos, const s3d::Vec2& size);
		[[nodiscard]] TexturePacker::Texture& operator()(double x, double y, double w, double h);

		[[nodiscard]] TexturePacker::Texture& resized(const s3d::Vec2& size);

		[[nodiscard]] TexturePacker::Texture& scaled(double scale);
		[[nodiscard]] TexturePacker::Texture& scaled(const s3d::Vec2& scale);
		[[nodiscard]] TexturePacker::Texture& scaled(double sx, double sy);

		[[nodiscard]] const TexturePacker::Texture& rotated(double angle);
		[[nodiscard]] const TexturePacker::Texture& rotatedAt(double x, double y, double angle);
		[[nodiscard]] const TexturePacker::Texture& rotatedAt(const s3d::Vec2& pos, double angle);

		[[nodiscard]] TexturePacker::Texture& mirrored(bool doMirror = true);
		[[nodiscard]] TexturePacker::Texture& fliped(bool doFlip = true);

		s3d::Quad draw(double x, double y, const s3d::ColorF& diffuse = s3d::Palette::White) const;

		s3d::Quad draw(const s3d::Vec2& pos, const s3d::ColorF& diffuse = s3d::Palette::White) const;

		s3d::Quad drawAt(double x, double y, const s3d::ColorF& diffuse = s3d::Palette::White) const;

		s3d::Quad drawAt(const s3d::Vec2& pos, const s3d::ColorF& diffuse = s3d::Palette::White) const;
	};

}