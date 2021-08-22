#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/base/IComponent.hpp>
namespace abyss::Event
{
    class IPlayerStateChanger
    {
    public:
        virtual ~IPlayerStateChanger() = default;

        virtual void onEventStart(Actor::ActorObj* player) = 0;
        virtual void onEventEnd(Actor::ActorObj* player) = 0;
    };
    /// <summary>
    /// プレイヤーのステート制御
    /// </summary>
    class PlayerStateCtrl :
        public IComponent
    {
    public:
        PlayerStateCtrl(IEvent* pEvent);

        void onStart() override;
        void onEnd() override;

        template<class Type, class... Args>
        PlayerStateCtrl& setChanger(Args&&... args)
        {
            return this->setChanger(std::make_shared<Type>(std::forward<Args>(args)...));
        }

        PlayerStateCtrl& setChanger(const std::shared_ptr<IPlayerStateChanger>& changer);
    private:
        IEvent* m_pEvent;
        std::shared_ptr<IPlayerStateChanger> m_changer;
    };
}