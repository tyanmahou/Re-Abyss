#include "SlimeView.hpp"
#include <domain/actor/SlimeActor.hpp>
#include <Siv3D.hpp>

namespace abyss
{
	abyss::SlimeView::SlimeView(std::shared_ptr<SlimeActor> pModel):
		m_texture(U"work/enemy/slime/slime.png"),
		m_pModel(pModel)
	{}
	void SlimeView::draw() const
	{
		auto pModel = m_pModel.lock();

		bool isLeft = pModel->getForward() == Forward::Left;
		auto& pos = pModel->getPos();

		switch (pModel->getMotion())
		{
		case SlimeActor::Motion::Walk: {
			int32 time = static_cast<int32>(Periodic::Square0_1(1s));
			auto tex = m_texture(40 * time,0, 40, 40);
			(isLeft ? tex : tex.mirrored()).drawAt(pos);
		}
		break;
		case SlimeActor::Motion::Jump: {
			int32 page = pModel->getVellocity().y > 0 ? 1 : 0;
			auto tex = m_texture(40 * page,40, 40, 40);
			(isLeft ? tex : tex.mirrored()).drawAt(pos);
		}break;
		default:
			break;
		}
#ifdef DEBUG
		pModel->region().draw(ColorF(1, 0, 0, 0.5));
#endif // DEBUG
	}
	bool SlimeView::isDelete() const
	{
		return m_pModel.expired();
	}
}
