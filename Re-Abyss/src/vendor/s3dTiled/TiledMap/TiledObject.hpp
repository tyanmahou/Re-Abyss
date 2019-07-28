#pragma once
#include<Siv3D/Vector2D.hpp>
#include<Siv3D/String.hpp>
#include<Siv3D/Optional.hpp>
#include<Siv3D/Shape.hpp>

#include "TiledDef.hpp"
#include "TiledProperty.hpp"

namespace s3dTiled
{
	class TiledObject
	{
		s3d::uint32 m_id;
		s3d::String m_name;
		s3d::String m_type;
		s3d::Vec2 m_pos;
		double m_rotation;
		s3d::Shape m_shape;
		TiledProperties m_props;
		s3d::Optional<GId> m_gId;
	public:
		TiledObject() = default;
		TiledObject(s3d::XMLElement xml, const  s3d::FilePath& parentPath = L"");
		// TiledObject(const s3d::JSONObject& json, const  s3d::FilePath& parentPath = L"");
	};
}