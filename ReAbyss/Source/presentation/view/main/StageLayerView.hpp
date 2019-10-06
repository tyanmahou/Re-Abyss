#pragma once
#include <Siv3D/String.hpp>
#include <Siv3D/Rectangle.hpp>
#include <functional>
#include <unordered_map>

namespace abyss
{
	class StageLayerView
	{
	private:
		std::unordered_map<s3d::String, std::function<void(const s3d::RectF&)>> m_layerViews;
	public:
		void addView(const s3d::String& layer, std::function<void(const s3d::RectF&)> callback)
		{
			m_layerViews[layer] = callback;
		}
		void draw(const s3d::String& layer, const s3d::RectF& rect)const
		{
			if (m_layerViews.find(layer) != m_layerViews.end()) {
				const auto& func = m_layerViews.at(layer);
				if (func) {
					func(rect);
				}
			}
		}
	};
}