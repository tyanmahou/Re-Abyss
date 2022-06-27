#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/modules/GlobalTime/GlobalTimeScale.hpp>
#include <abyss/components/Event/base/ILastUpdate.hpp>

namespace abyss::Event
{
    class GlobalTimeCtrl :
        public IComponent,
        public ILastUpdate
    {
    public:
        GlobalTimeCtrl(EventObj* pEvent);

        void onStart() override;
        void onLastUpdate() override;
    private:
        EventObj* m_pEvent;
        std::shared_ptr<GlobalTimeScale> m_timeScaleModel;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Event::GlobalTimeCtrl>
    {
        using Base = MultiComponents<
            Event::ILastUpdate
        >;
    };
}
