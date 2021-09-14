#pragma once
#include <memory>
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Event/base/IStream.hpp>

namespace abyss::Event
{
    class StreamHandler : public IComponent
    {
    public:
        StreamHandler(IEvent* m_pEvent);

        void setup(Executer executer) override;

        void onStart() override;

        bool update();
    private:
        IEvent* m_pEvent;
        std::unique_ptr<Coro::Task<>> m_stream;
    };
}