#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/modules/Temporary/TempFrag/TempKey.hpp>

namespace abyss::Adv
{
    /// <summary>
    /// イベント制御
    /// </summary>
    class EventCtrl :
        public IComponent
    {
    public:
        EventCtrl(AdvObj* pTalk, s3d::uint32 eventId);

        void requestComplete();
    public:
        void onStart() override;
    private:
        TempKey tempKey() const;
    private:
        AdvObj* m_pTalk;
        s3d::uint32 m_eventId;
    };
}
