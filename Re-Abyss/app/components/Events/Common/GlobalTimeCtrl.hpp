#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Events/base/ILastUpdate.hpp>
#include <abyss/models/GlobalTime/GlobalTimeScaleModel.hpp>

namespace abyss::Event
{
    class GlobalTimeCtrl :
        public IComponent,
        public ILastUpdate
    {
    public:
        GlobalTimeCtrl(IEvent* pEvent);

        void onStart() override;
        void onLastUpdate() override;
    private:
        IEvent* m_pEvent;
        std::shared_ptr<GlobalTimeScaleModel> m_timeScaleModel;
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