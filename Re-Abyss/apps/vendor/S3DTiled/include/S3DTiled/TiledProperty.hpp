#pragma once

#include<Siv3D/Fwd.hpp>
#include<Siv3D/Color.hpp>

namespace s3dTiled
{
		/// <summary>
		/// Tiledのプロパティ
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
				double f;
				s3d::int32 i;
				s3d::String* str;
			}m_storage;

			void reset(Type type);
		public:
			TiledProperty();
			TiledProperty(const TiledProperty& other);
			TiledProperty(TiledProperty&& other);

			TiledProperty(bool b);
			TiledProperty(const s3d::Color& col);
			TiledProperty(double f);
			TiledProperty(s3d::int32 i);
			TiledProperty(const s3d::String& str);

			~TiledProperty();

			bool toBool() const;
			operator bool() const;

			s3d::Color toColor() const;
			operator s3d::Color() const;

			double toFloat() const;
			operator double() const;

			s3d::int32 toInt() const;
			operator s3d::int32() const;

			const s3d::String& toString() const;
			operator s3d::String() const;

			Type getType()const;

			void clear();

			TiledProperty& operator =(const TiledProperty& other);
			TiledProperty& operator =(TiledProperty&& other);
		};
}