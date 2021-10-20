#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/Ref/Ref.hpp>
#include <abyss/components/Novel/base/ICommand.hpp>
#include <Siv3D/Vector2D.hpp>

namespace abyss::Actor::Enemy::CodeZero::Demo
{
    class DemoCtrl;
}
namespace abyss::Novel::BossTalk0_0
{
    class BossMove :
        public ICommand
    {
    public:
        BossMove(TalkObj* pTalk);

        void onStart()override;
        Coro::Task<> onCommand() override;
        void onEnd() override;
    private:
        TalkObj* m_pTalk;
        Ref<Actor::Enemy::CodeZero::Demo::DemoCtrl> m_codeZeroDemo;

        s3d::Vec2 m_initPos;
        s3d::Vec2 m_targetPos;

        Ref<QuakeModel> m_quake;
        Ref<QuakeModel> m_lastQuake;
    };
}