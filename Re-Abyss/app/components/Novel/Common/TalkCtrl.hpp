#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/components/Actor/Common/ILocator.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Novel
{
    /// <summary>
    /// 会話制御
    /// </summary>
    class TalkCtrl :
        public IComponent
    {
    public:
        TalkCtrl(TalkObj* pTalk);

        void request();
        void resume();

        TalkCtrl& setLocator(Ref<Actor::ILocator> locator)
        {
            m_pTargetLocator = locator;
            return *this;
        }
    private:
        TalkObj* m_pTalk;
        Ref<Actor::ILocator> m_pTargetLocator;
    };
}
