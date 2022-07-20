#pragma once
#include <abyss/components/Actor/Player/State/BaseState.hpp>

namespace abyss::Actor::Player
{
    class TalkState final : public BaseState
    {
    public:
        static void Change(ActorObj* pActor, const Ref<ILocator>& pTargetLocator = nullptr);
    public:
        TalkState(const Ref<ILocator>& pTargetLocator = nullptr);
    private:
        void onLanding()override;

        void start()override;
        void end()override;
        void update()override;
        void lastUpdate()override;
    private:
        Ref<ILocator> m_pTargetLocator;
    };
}
