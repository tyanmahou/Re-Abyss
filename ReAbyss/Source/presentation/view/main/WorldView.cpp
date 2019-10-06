#include "WorldView.hpp"
#include "object/IWorldObjectView.hpp"
#include <Siv3D.hpp>

namespace abyss
{
	void WorldView::addView(std::unique_ptr<IWorldObjectView>&& view)
	{
		view->setWorldView(this);
		view->start();
		m_objectViews.push_back(std::move(view));
	}

	void WorldView::update()
	{
		for (auto&& obj : m_objectViews) {
			obj->update();
		}

		// delete
		s3d::Erase_if(m_objectViews, [](const Views::value_type & obj) {
			return obj->isDelete();
		});
	}

	void WorldView::draw() const
	{
		// draw
		for (auto&& obj : m_objectViews) {
			obj->draw();
		}

		m_effect.update();
	}
	s3d::Effect& WorldView::getEffect()
	{
		return m_effect;
	}
}
