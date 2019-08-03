#pragma once
#include<Siv3D/Vector2D.hpp>
#include<Siv3D/String.hpp>
#include<Siv3D/Optional.hpp>
#include<Siv3D/Shape.hpp>

#include "TiledDef.hpp"
#include "TiledProperty.hpp"

namespace s3dTiled
{
	struct TiledObject
	{
		s3d::uint32 id;
		s3d::String name;
		s3d::String type;
		s3d::Vec2 pos;
		double rotation;
		s3d::Shape shape;
		TiledProperties props;
		s3d::Optional<GId> gId;

		void setProps(TiledProperties&& props);
		s3d::Optional<TiledProperty> getProperty(const s3d::String& name) const;
	};
}