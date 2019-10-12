#include "WorldView.hpp"
#include <domain/model/WorldModel.hpp>
#include <domain/actor/IActor.hpp>

#include <Siv3D.hpp>

namespace abyss
{
	void WorldView::draw() const
	{
		// draw
		m_pModel->draw();
		m_effect.update();
	}
	s3d::Effect& WorldView::getEffect()
	{
		return m_effect;
	}
}
