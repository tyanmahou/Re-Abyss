#include <abyss/components/Actor/Gimmick/CodeZeroBack/Main.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/modules/Actor/Actors.hpp>
#include <abyss/modules/Stage/Stage.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/HideCtrl.hpp>

namespace abyss::Actor::Gimmick::CodeZeroBack
{
    Main::Main(ActorObj* pActor, const s3d::Vec2& pos):
        m_pActor(pActor),
        m_pos(pos)
    {}

    void Main::onStart()
    {
    }
    void Main::onPreDraw()
    {
        if (m_hideCtrl = m_pActor->getModule<Actors>()->find<Enemy::CodeZero::HideCtrl>()) {
            m_isFind = true;
        }
    }
    void Main::onDraw() const
    {
        double alpha = 1.0;
        if (m_isFind) {
            if (m_hideCtrl) {
                alpha = m_hideCtrl->calcBackAlpha();
            } else {
                alpha = 0;
            }
        }
        if (auto room = m_pActor->getModule<Stage>()->findRoom(m_pos)) {
            // 移動開始
            room->getRegion().draw(ColorF(0, alpha));
        }
    }
}
