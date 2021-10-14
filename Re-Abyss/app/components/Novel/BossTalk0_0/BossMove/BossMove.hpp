#pragma once
#include <abyss/utils/Ref/Ref.hpp>
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Novel/base/ITalker.hpp>
#include <Siv3D/Vector2D.hpp>

namespace abyss::Actor::Enemy::CodeZero::Demo
{
    class DemoCtrl;
}
namespace abyss::Novel::BossTalk0_0
{
    class BossMove :
        public IComponent,
        public ITalker
    {
    public:
        BossMove(TalkObj* pTalk);

        void onStart()override;
        Coro::Task<> onTalk() override;
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

namespace abyss
{
    template<>
    struct ComponentTree<Novel::BossTalk0_0::BossMove>
    {
        using Base = MultiComponents<
            Novel::ITalker
        >;
    };
}