#pragma once
#include <memory>
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/components/Event/base/IStream.hpp>

namespace abyss::Event
{
    class StreamHandler : public IComponent
    {
    public:
        StreamHandler(EventObj* m_pEvent);

        void setup(Executer executer) override;

        void onStart() override;

        bool update();
    private:
        EventObj* m_pEvent;
        std::unique_ptr<Coro::Fiber<>> m_stream;
    };
}