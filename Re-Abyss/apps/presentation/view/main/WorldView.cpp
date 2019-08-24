#include "WorldView.hpp"
#include "object/IWorldObjectView.hpp"
#include <Siv3D.hpp>

namespace abyss
{
	void WorldView::addView(std::unique_ptr<IWorldObjectView>&& view, s3d::int32 layer)
	{
		m_objectViews.emplace(layer, std::move(view));
	}

	void WorldView::update()
	{
		for (auto&& obj : m_objectViews) {
			obj.second->update();
		}

		// delete
		for (auto it = m_objectViews.begin(); it != m_objectViews.end();) {
			if (it->second->isDelete()) {
				it = m_objectViews.erase(it);
			}
			else {
				++it;
			}
		}
	}

	void WorldView::draw() const
	{
		// draw
		for (auto&& obj : m_objectViews) {
			obj.second->draw();
		}
	}
}
