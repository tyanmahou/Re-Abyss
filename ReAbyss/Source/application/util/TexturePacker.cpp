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
	class TexturePacker::Impl
	{
		struct Info
		{
			Vec2 pos;
			Vec2 size;
		};
		Texture m_texture;
		std::unordered_map<String, Info> m_infos;

		void load(const s3d::FilePath& json)
		{
			JSONReader reader(json);
			if (!reader) {
				return;
			}
			for (const auto& elm : reader[U"frames"].arrayView()) {
				const auto& frame = elm[U"frame"];
				Info info;
				info.pos = {
					frame[U"x"].get<double>(),
					frame[U"y"].get<double>(),
				};
				info.size = {
					frame[U"w"].get<double>(),
					frame[U"h"].get<double>(),
				};
				m_infos[elm[U"filename"].getString()] = info;
			}
			if (!m_texture) {
				const FilePath& parent = FileSystem::ParentPath(json);
				m_texture = Texture(parent + reader[U"meta.image"].getString());
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

		TextureRegion operator()(const s3d::String& fileName) const
		{
			const Info& info = m_infos.at(fileName);
			return m_texture(info.pos, info.size);
		}

		TextureRegion operator()(const s3d::String& fileName, const s3d::Vec2& pos, const s3d::Vec2& size) const
		{
			const Info& info = m_infos.at(fileName);
			return m_texture(s3d::Math::Ceil(info.pos + pos), s3d::Math::Ceil(size));
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
	s3d::TextureRegion TexturePacker::operator()(const s3d::String& fileName) const
	{
		return (*pImpl)(fileName);
	}
	s3d::TextureRegion TexturePacker::operator()(const s3d::String& fileName, const s3d::Vec2& pos, const s3d::Vec2& size) const
	{
		return (*pImpl)(fileName, pos, size);
	}
}