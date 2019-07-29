#pragma once
#include<Siv3D/Fwd.hpp>
#include<Siv3D/Color.hpp>

#include<unordered_map>

namespace s3dTiled
{
		/// <summary>
		/// Tiled�̃v���p�e�B
		/// </summary>
		class TiledProperty
		{
		public:
			enum class Type
			{
				Bool,
				Color,
				Float,
				Int,
				String,
				None,
			};
		private:
			Type m_type;
			union
			{
				bool b;
				s3d::Color col;
				float f;
				s3d::int32 i;
				s3d::String* str;
			};
		public:
			TiledProperty();
			TiledProperty(s3d::XMLElement xml, const s3d::FilePath& parentPath = L"");
			// TiledProperty(const s3d::JSONObject& xml, const s3d::FilePath& parentPath);

			TiledProperty(const TiledProperty& other);
			// TiledProperty(TiledProperty&& other);

			~TiledProperty();

			bool toBool() const;
			s3d::Color toColor() const;
			float toFloat() const;
			s3d::int32 toInt() const;
			const s3d::String& toString() const;

			Type getType()const;

			void clear();

			TiledProperty& operator =(const TiledProperty& other);
			// TiledProperty& operator =(TiledProperty&& other);
		};

		/// <summary>
		/// �v���p�e�B�̃}�b�v
		/// </summary>
		using TiledProperties = std::unordered_map<s3d::String, TiledProperty>;

		/// <summary>
		/// �v���p�e�B�̃Z�b�g
		/// </summary>
		void ParseProps(s3d::XMLElement map, TiledProperties& props, const s3d::FilePath& parentPath);
}