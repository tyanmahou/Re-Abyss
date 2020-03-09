#include "SlimeView.hpp"
#include <Siv3D.hpp>

namespace abyss
{
    SlimeView::SlimeView() :
        m_texture(U"work/enemy/slime/slime.png")
    {}

    void SlimeView::setViewModel(const SlimeViewModel& viewModel)
    {
        m_viewModel = viewModel;
    }

    void SlimeView::draw() const
    {
        auto&& [motion, forward, pos, vellocity] = m_viewModel;

        bool isLeft = forward == Forward::Left;
        switch (motion) {
        case SlimeActor::Motion::Walk:
        {
            int32 time = static_cast<int32>(Periodic::Square0_1(1s));
            auto tex = m_texture(40 * time, 0, 40, 40);
            (isLeft ? tex : tex.mirrored()).drawAt(pos);
        }
        break;
        case SlimeActor::Motion::Jump:
        {
            int32 page = vellocity.y > 0 ? 1 : 0;
            auto tex = m_texture(40 * page, 40, 40, 40);
            (isLeft ? tex : tex.mirrored()).drawAt(pos);
        }break;
        default:
            break;
        }
    }
}
