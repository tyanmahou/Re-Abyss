#pragma once
#include <abyss/components/Event/Common/PlayerStateCtrl.hpp>
#include <abyss/components/Actor/base/ILocator.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Event::Talk
{
    class PlayerStateChanger final: public IPlayerStateChanger
    {
    public:
        PlayerStateChanger(const Ref<Actor::ILocator>& pTargetLocator = nullptr):
            m_pTargetLocator(pTargetLocator)
        {}
        void onEventStart(Actor::ActorObj* player) override;
        void onEventEnd(Actor::ActorObj* player) override;
    private:
        Ref<Actor::ILocator> m_pTargetLocator;
    };
}