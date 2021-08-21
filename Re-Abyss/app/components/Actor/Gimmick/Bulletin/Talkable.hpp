#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Actor/Player/IGimmickReactor.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Actor::Gimmick::Bulletin
{
    class Talkable :
        public IComponent,
        public Player::IGimmickReactor
    {
    public:
        Talkable(ActorObj* pActor);

        void onStart() override;
        void onEnd() override;
        void onGimmickReact(ActorObj* player) override;

        double getOffsetY() const
        {
            return m_offsetY;
        }
        void setOffsetY(double offsetY)
        {
            m_offsetY = offsetY;
        }
    private:
        ActorObj* m_pActor;
        Ref<UI::UIObj> m_balloon;
        double m_offsetY = -65.0;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::Gimmick::Bulletin::Talkable>
    {
        using Base = Actor::Player::IGimmickReactor;
    };
}