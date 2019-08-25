#pragma once
#include <Siv3D/String.hpp>
#include <functional>
namespace abyss
{
	struct LayerViewEntity
	{
		s3d::String layerName;
		std::function<void(const s3d::RectF&)> drawCallback;
		LayerViewEntity(const s3d::String& name, std::function<void(const s3d::RectF&)> callback) :
			layerName(name),
			drawCallback(callback)
		{}
	};
}