#pragma once
#if ABYSS_DEBUG

#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/modules/Devs/WorldComment/WorldComment.hpp>
#include <abyss/modules/Actor/base/IPreDraw.hpp>
#include <abyss/components/Actor/Common/Body.hpp>
#include <abyss/components/Actor/Common/BehaviorCtrl.hpp>
#include <abyss/utils/Coro/Fiber/Fiber.hpp>

#include <Siv3D/Array.hpp>
#include <Siv3D/String.hpp>
namespace abyss::Actor
{
    class BehaviorTest :
        public IComponent,
        public IPreDraw
    {
        using BehaviorFunc = std::function<Coro::Fiber<>(ActorObj*)>;
    public:
        BehaviorTest(ActorObj* pActor);

        void onStart() override;
        void onPreDraw() override;

        BehaviorTest& setInitializer(const BehaviorFunc& initializer);
        BehaviorTest& setWaitAction(const BehaviorFunc& waitAction);
        BehaviorTest& registAction(const s3d::String& key, const BehaviorFunc& behavior);
    private:
        Coro::AsyncGenerator<BehaviorFunc> doTest(ActorObj* pActor);
    private:
        ActorObj* m_pActor;
        std::unique_ptr<WorldComment::Requestor> m_worldComment;
        Ref<Body> m_body;

        BehaviorFunc m_initializer;
        BehaviorFunc m_waitAction;
        s3d::Array<std::pair<s3d::String, BehaviorFunc>> m_actions;
        size_t m_select = 0;
        bool m_isSelectable = false;
        bool m_isActive = false;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::BehaviorTest>
    {
        using Base = Actor::IPreDraw;
    };
}
#endif