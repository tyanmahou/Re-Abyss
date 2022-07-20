#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/GameObject/IComponent.hpp>

namespace abyss::Novel
{
    /// <summary>
    /// プレイヤー制御
    /// </summary>
    class PlayerCtrl :
        public IComponent
    {
    public:
        PlayerCtrl(TalkObj* pTalk);

        void request(std::function<void(Actor::ActorObj*)> callback);
    private:
        TalkObj* m_pTalk;
    };
}
