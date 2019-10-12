#include "SlimeView.hpp"
#include <domain/actor/SlimeActor.hpp>
#include <Siv3D.hpp>

namespace abyss
{
	SlimeView::SlimeView(const SlimeActor* pModel):
		m_texture(U"work/enemy/slime/slime.png"),
		m_pModel(pModel)
	{}
	void SlimeView::draw() const
	{
		bool isLeft = m_pModel->getForward() == Forward::Left;
		auto& pos = m_pModel->getPos();

		switch (m_pModel->getMotion())
		{
		case SlimeActor::Motion::Walk: {
			int32 time = static_cast<int32>(Periodic::Square0_1(1s));
			auto tex = m_texture(40 * time,0, 40, 40);
			(isLeft ? tex : tex.mirrored()).drawAt(pos);
		}
		break;
		case SlimeActor::Motion::Jump: {
			int32 page = m_pModel->getVellocity().y > 0 ? 1 : 0;
			auto tex = m_texture(40 * page,40, 40, 40);
			(isLeft ? tex : tex.mirrored()).drawAt(pos);
		}break;
		default:
			break;
		}
#ifdef DEBUG
		m_pModel->region().draw(ColorF(1, 0, 0, 0.5));
#endif // DEBUG
	}
}
